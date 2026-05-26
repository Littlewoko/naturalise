#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include "rules/comment_rule.h"
#include <string>

using namespace std;

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
        REQUIRE(res[0].line_number == 50);
        REQUIRE_THAT(res[0].message, Catch::Matchers::ContainsSubstring("must begin with *"));}
}