#pragma once
#include "base_rule.h"

class CommentRule: public BaseRule {
public:
    CommentRule() = default;
    ~CommentRule() = default;

    bool should_run(ChunkType type) override;
    void validate(const Chunk &chunk, vector<Violation> &Violations) override;
};