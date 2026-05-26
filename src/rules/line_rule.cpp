#include "line_rule.h"

namespace {
    void check_trailing_whitespace(int line_number, const string &line, vector<Violation> &violations) {
        if (line.empty()) return;

        if (isspace(static_cast<unsigned char>(line.back()))) {
            Violation violation;
            violation.level = ViolationLevel::WARN;
            violation.line_number = line_number;
            violation.message = "line should not contain trailing whitespace";

            violations.push_back(violation);
        }
    }

    void check_over_length(int line_number, const string &line, vector<Violation> &violations) {
        if(!line.empty() && line.size() > 80) {
            Violation violation;
            violation.level = ViolationLevel::WARN;
            violation.line_number = line_number;
            violation.message = "line should not be greater than 80 characters";

            violations.push_back(violation);
        }
    }
}

bool LineRule::should_run(ChunkType) {
    return true;
}

void LineRule::validate(const Chunk &chunk, vector<Violation> &violations) {
    int line_number = chunk.starting_line;
    for (const string &line : chunk.lines) {
        check_trailing_whitespace(line_number, line, violations);
        check_over_length(line_number, line, violations);

        ++line_number;
    }
}