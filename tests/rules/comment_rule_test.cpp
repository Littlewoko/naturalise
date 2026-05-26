#include <catch2/catch_test_macros.hpp>
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

    // SECTION("VALID: Line must begin with a *") {
    //     vector<string> lines {"*"};

       
    // }
}