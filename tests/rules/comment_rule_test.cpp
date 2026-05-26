#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include "rules/comment_rule.h"
#include <string>

using namespace std;

const string _asterix_warning = "line should begin with *";
const string _trailing_whitespace_warning = "line should not contain trailing whitespace";
const string _over_length_line = "line should not be greater than 80 characters";

auto has_violation = [](const vector<Violation> &violations, int line, const string &message, ViolationLevel level) {
    for (auto const &v: violations) {
        if (v.level == level 
        && v.line_number == line
        && v.message.find(message)) {
            return true;
        }
    }

    return false;
};

TEST_CASE("Comment Line Validator") {
    CommentRule rule;

    SECTION("VALID: validator runs on ChunkType CommentBlock") {
        ChunkType type {ChunkType::CommentBlock};

        bool res = rule.should_run(type);

        REQUIRE(res == true);
    }

    SECTION("INVALID: validator runs on ChunkType CommentBlock") {
        ChunkType type {ChunkType::Other};

        bool res = rule.should_run(type);

        REQUIRE(res == false);
    }

    SECTION("VALID: Line must begin with a *") {
        vector<string> lines {"*"};

        Chunk chunk;
        chunk.starting_line = 0;
        chunk.type = ChunkType::CommentBlock;
        chunk.lines = lines;

        vector<Violation> res;

        rule.validate(chunk, res);

        REQUIRE(res.size() == 0);
    }

    SECTION("INVALID: Line must begin with a *") {
        vector<string> lines {"hello"};

        Chunk chunk;
        chunk.starting_line = 50;
        chunk.type = ChunkType::CommentBlock;
        chunk.lines = lines;

        vector<Violation> res;

        rule.validate(chunk, res);

        REQUIRE(res.size() == 1);
        REQUIRE(res[0].level == ViolationLevel::WARN);
        REQUIRE(res[0].line_number == 50);
        REQUIRE_THAT(res[0].message, Catch::Matchers::ContainsSubstring(_asterix_warning));    
    }

    SECTION("INVALID: empty string") {
        vector<string> lines {""};

        Chunk chunk;
        chunk.starting_line = 50;
        chunk.type = ChunkType::CommentBlock;
        chunk.lines = lines;

        vector<Violation> res;

        rule.validate(chunk, res);

        REQUIRE(res.size() == 1);
        REQUIRE(res[0].level == ViolationLevel::WARN);
        REQUIRE(res[0].line_number == 50);
        REQUIRE_THAT(res[0].message, Catch::Matchers::ContainsSubstring(_asterix_warning));    
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
        bool has_no_asterix = has_violation(res, chunk.starting_line, _asterix_warning, ViolationLevel::WARN);

        REQUIRE(has_trailing_whitespace == true);    
        REQUIRE(has_no_asterix == true);   
    }

    SECTION("INVALID: trailing whitespace") {
        vector<string> lines {"* "};

        Chunk chunk;
        chunk.starting_line = 30;
        chunk.type = ChunkType::CommentBlock;
        chunk.lines = lines;

        vector<Violation> res;

        rule.validate(chunk, res);

        REQUIRE(res.size() == 1);
        REQUIRE(res[0].level == ViolationLevel::WARN);
        REQUIRE(res[0].line_number == 30);
        REQUIRE_THAT(res[0].message, Catch::Matchers::ContainsSubstring(_trailing_whitespace_warning));    
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

        REQUIRE(res.size() == 1);
        REQUIRE(res[0].level == ViolationLevel::WARN);
        REQUIRE(res[0].line_number == 30);
        REQUIRE_THAT(res[0].message, Catch::Matchers::ContainsSubstring(_over_length_line));    
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

    SECTION("INVALID: triple combo") {
        string line(100, ' ');
        vector<string> lines {line};

        Chunk chunk;
        chunk.starting_line = 30;
        chunk.type = ChunkType::CommentBlock;
        chunk.lines = lines;

        vector<Violation> res;

        rule.validate(chunk, res);

        bool has_trailing_whitespace = has_violation(res, chunk.starting_line, _trailing_whitespace_warning, ViolationLevel::WARN);
        bool has_no_asterix = has_violation(res, chunk.starting_line, _asterix_warning, ViolationLevel::WARN);
        bool is_too_long = has_violation(res, chunk.starting_line, _over_length_line, ViolationLevel::WARN);

        REQUIRE(has_trailing_whitespace == true);    
        REQUIRE(has_no_asterix == true);  
        REQUIRE(is_too_long == true);
    }
}