#pragma once
#include "utils/types.h"

class BaseRule {
public:
    virtual ~BaseRule() = default;
    virtual bool should_run(ChunkType) = 0;
    virtual void validate(const Chunk&, vector<string> &violations) = 0;
};