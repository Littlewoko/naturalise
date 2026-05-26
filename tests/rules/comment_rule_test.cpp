#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include "rules/comment_rule.h"
#include <string>
#include "util/test_helper.h"

using namespace std;

const string _asterisk_warning = "line should begin with *";

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

        bool has_no_asterix = TestUtil::has_violation(res, 
            chunk.starting_line, 
            _asterisk_warning, 
            ViolationLevel::WARN);

        REQUIRE(has_no_asterix == true);     
    }

    SECTION("INVALID: empty string") {
        vector<string> lines {""};

        Chunk chunk;
        chunk.starting_line = 50;
        chunk.type = ChunkType::CommentBlock;
        chunk.lines = lines;

        vector<Violation> res;

        rule.validate(chunk, res);

        bool has_no_asterix = TestUtil::has_violation(res, 
            chunk.starting_line, 
            _asterisk_warning, 
            ViolationLevel::WARN);

        REQUIRE(has_no_asterix == true);     
    }

    SECTION("INVALID: whitespace string") {
        vector<string> lines {"    "};

        Chunk chunk;
        chunk.starting_line = 25;
        chunk.type = ChunkType::CommentBlock;
        chunk.lines = lines;

        vector<Violation> res;

        rule.validate(chunk, res);

        bool has_no_asterix = TestUtil::has_violation(res, 
            chunk.starting_line, 
            _asterisk_warning, 
            ViolationLevel::WARN);

        REQUIRE(has_no_asterix == true);   
    }

    SECTION("INVALID: all * except first") {
        string line(81, '*');
        line[0] = 'X';
        vector<string> lines {line};

        Chunk chunk;
        chunk.starting_line = 30;
        chunk.type = ChunkType::CommentBlock;
        chunk.lines = lines;

        vector<Violation> res;

        rule.validate(chunk, res);

        bool has_no_asterix = TestUtil::has_violation(res, 
            chunk.starting_line, 
            _asterisk_warning, 
            ViolationLevel::WARN);

        REQUIRE(has_no_asterix == true);   
    }

    SECTION("VALID: all *") {
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
}