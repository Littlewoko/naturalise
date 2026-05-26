#include <catch2/catch_test_macros.hpp>
#include "pipeline/pipeline.h"
#include <string>

using namespace std;

class PassthroughFake: public BaseRule {
public:
    bool should_run(ChunkType) override { return false;}
    void validate(const Chunk&, vector<Violation> &violations) override {
        Violation empty;
        violations.push_back(empty);
    }
};

class EnforcingFake: public BaseRule {
public:
    bool should_run(ChunkType) override { return true;}
    void validate(const Chunk& chunk, vector<Violation> &violations) override {
        Violation res;
        res.level = ViolationLevel::WARN;
        res.line_number = chunk.starting_line;
        res.message = "triggered by fake";
        violations.push_back(res);
    }
};

TEST_CASE("rule pipeline core loop") {
    SECTION("Empty chunks collection returns empty violations") {
        PassthroughFake pass;
        EnforcingFake enf;

        RulePipeline pipeline({ &pass, &enf });

        vector<Chunk> empty;

        auto violations = pipeline.run(empty);

        REQUIRE(violations.empty() == true);
    }

    SECTION("Execute rules on valid chunks and populate violations") {
        EnforcingFake enf;

        RulePipeline pipeline({ &enf });

        Chunk dummy;
        dummy.type = ChunkType::CommentBlock;
        dummy.starting_line = 15;
        dummy.lines = {"* test"};

        vector<Chunk> chunks{dummy};

        auto violations = pipeline.run(chunks);

        REQUIRE(violations.size() == 1);
        REQUIRE(violations[0].line_number == 15);
        REQUIRE(violations[0].message.find("triggered by fake") != string::npos);
    }

    SECTION("Rules only run if should run returns true") {
        PassthroughFake pass;

        RulePipeline pipeline({ &pass });

        Chunk dummy;
        dummy.type = ChunkType::CommentBlock;
        dummy.starting_line = 15;
        dummy.lines = {"* test"};

        vector<Chunk> chunks{dummy};

        auto violations = pipeline.run(chunks);

        REQUIRE(violations.empty() == true);
    }
}