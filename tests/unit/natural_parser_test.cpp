#include <catch2/catch_test_macros.hpp>
#include "parser/natural_parser.h"
#include <string>

using namespace std;

TEST_CASE("Natural Source Header Validation", "[parser]") {
    NaturalParser parser;

    SECTION("Valid header returns true and zero errors") {
        string valid = "* >Natural Source Header 000000\n* :Mode S\n";
        auto res = parser.validate(valid);

        REQUIRE(res.has_valid_header == true);
        REQUIRE(res.error_count == 0);
    }

    SECTION("Missing header flags an error") {
        string invalid = "DEFINE DATA LOCAL\nEND\n";
        auto res = parser.validate(invalid);

        REQUIRE(res.has_valid_header == false);
        REQUIRE(res.error_count == 1);
    }
}