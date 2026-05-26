#include <catch2/catch_test_macros.hpp>
#include "chunker/chunker.h"
#include "util/test_helper.h"
#include <sstream>

using namespace std;

TEST_CASE("Chunker state machine") {
    Chunker chunker;

    SECTION("An empty stream produces zero chunks") {
        stringstream input("");

        vector<Chunk> res = chunker.chunk(input);

        REQUIRE(res.size() == 0);
    }

    SECTION("Extracts a single isolated comment block chunk") {
        stringstream input;
        input << "* first line\n";
        input << "* second line\n";

        vector<Chunk> res = chunker.chunk(input);

        REQUIRE(res.size() == 1);
        REQUIRE(res[0].type == ChunkType::CommentBlock);
        REQUIRE(res[0].starting_line == 1); // lines are 1 indexed
        REQUIRE(res[0].lines.size() == 2);
        REQUIRE(res[0].lines[0] == "* first line"); // retain order
    }
}