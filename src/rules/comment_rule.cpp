#include "comment_rule.h"

bool CommentRule::should_run(ChunkType type) {
    return type == ChunkType::CommentBlock;
}

void CommentRule::validate(const Chunk &chunk, vector<Violation> &violations) {
    if (chunk.type == ChunkType::CommentBlock) {
        Violation violation;
        violation.line_number = 0;
        violation.message = "abc";
        violations.push_back(violation);
    }
}