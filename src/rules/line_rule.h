#pragma once
#include "base_rule.h"

class LineRule: public BaseRule {
public:
    LineRule() = default;
    ~LineRule() = default;

    bool should_run(ChunkType type) override;
    void validate(const Chunk &chunk, vector<Violation> &Violations) override;
};