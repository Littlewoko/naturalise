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
}