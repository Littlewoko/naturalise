#include "comment_rule.h"

namespace {
    void check_comment_start(int line_number, const string &line, vector<Violation> &violations) {
        if (line.empty() || line[0] != '*') {
            Violation violation;
            violation.level = ViolationLevel::WARN;
            violation.line_number = line_number;
            violation.message = "comment line must begin with *";

            violations.push_back(violation);
        }
    }
}

bool CommentRule::should_run(ChunkType type) {
    return type == ChunkType::CommentBlock;
}

void CommentRule::validate(const Chunk &chunk, vector<Violation> &violations) {
    int line_number = chunk.starting_line;
    for (const string &line : chunk.lines) {
        check_comment_start(line_number, line, violations);
        ++line_number;
    }
}