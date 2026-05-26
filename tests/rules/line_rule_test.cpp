#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include "rules/line_rule.h"
#include <string>

using namespace std;

const string _trailing_whitespace_warning = "line should not contain trailing whitespace";
const string _over_length_line = "line should not be greater than 80 characters";

auto has_violation = [](const vector<Violation> &violations, int line, const string &message, ViolationLevel level) {
    for (auto const &v: violations) {
        if (v.level == level 
        && v.line_number == line
        && (v.message.find(message) != string::npos)) {
            return true;
        }
    }

    return false;
};

TEST_CASE("Line Validator") {
    LineRule rule;

    SECTION("VALID: validator runs on any chunk type") {
        ChunkType type {ChunkType::CommentBlock};

        bool res = rule.should_run(type);

        REQUIRE(res == true);
    }

    SECTION("VALID: empty string") {
        vector<string> lines {""};

        Chunk chunk;
        chunk.starting_line = 50;
        chunk.type = ChunkType::CommentBlock;
        chunk.lines = lines;

        vector<Violation> res;

        rule.validate(chunk, res);

        REQUIRE(res.size() == 0);
    }

    SECTION("INVALID: whitespace string") {
        vector<string> lines {"    "};

        Chunk chunk;
        chunk.starting_line = 25;
        chunk.type = ChunkType::CommentBlock;
        chunk.lines = lines;

        vector<Violation> res;

        rule.validate(chunk, res);

        bool has_trailing_whitespace = has_violation(res, chunk.starting_line, _trailing_whitespace_warning, ViolationLevel::WARN);

        REQUIRE(has_trailing_whitespace == true);    
    }

    SECTION("INVALID: trailing whitespace") {
        vector<string> lines {"ABC "};

        Chunk chunk;
        chunk.starting_line = 30;
        chunk.type = ChunkType::CommentBlock;
        chunk.lines = lines;

        vector<Violation> res;

        rule.validate(chunk, res);

        bool has_trailing_whitespace = has_violation(res, chunk.starting_line, _trailing_whitespace_warning, ViolationLevel::WARN);

        REQUIRE(has_trailing_whitespace == true);      
    }

    SECTION("INVALID: over length") {
        string line(81, '*');
        vector<string> lines {line};

        Chunk chunk;
        chunk.starting_line = 30;
        chunk.type = ChunkType::CommentBlock;
        chunk.lines = lines;

        vector<Violation> res;

        rule.validate(chunk, res);

        bool has_over_length_line = has_violation(res, chunk.starting_line, _over_length_line, ViolationLevel::WARN);

        REQUIRE(has_over_length_line == true); 
    }

    SECTION("VALID: at length") {
        string line(80, '*');
        vector<string> lines {line};

        Chunk chunk;
        chunk.starting_line = 30;
        chunk.type = ChunkType::CommentBlock;
        chunk.lines = lines;

        vector<Violation> res;

        rule.validate(chunk, res);

        REQUIRE(res.size() == 0);
    }

    SECTION("INVALID: double combo") {
        string line(100, ' ');
        vector<string> lines {line};

        Chunk chunk;
        chunk.starting_line = 30;
        chunk.type = ChunkType::CommentBlock;
        chunk.lines = lines;

        vector<Violation> res;

        rule.validate(chunk, res);

        bool has_trailing_whitespace = has_violation(res, chunk.starting_line, _trailing_whitespace_warning, ViolationLevel::WARN);
        bool is_too_long = has_violation(res, chunk.starting_line, _over_length_line, ViolationLevel::WARN);

        REQUIRE(has_trailing_whitespace == true);    
        REQUIRE(is_too_long == true);
    }
}