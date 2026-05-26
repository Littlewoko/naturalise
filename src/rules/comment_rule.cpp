#include "comment_rule.h"

bool CommentRule::should_run(ChunkType type) {
    return false;
}

void CommentRule::validate(const Chunk &chunk, vector<Violation> &violations) {
    
}