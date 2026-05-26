#pragma once
#include <vector>
#include <string>
#include <iostream>

using namespace std;

enum class ChunkType {
    CommentBlock,
    Other
};

enum class ViolationLevel {
    WARN,
    ERROR
};

inline ostream& operator<<(ostream &os, const ViolationLevel &level) {
    switch (level) {
        case ViolationLevel::WARN:
            os << "WARN";
            break;
        case ViolationLevel::ERROR:
            os << "ERROR";
            break;
        default:
            os << "UNKNOWN";
            break;
    }

    return os;
}

struct Violation {
    ViolationLevel level;
    int line_number;
    string message;
};

struct Chunk {
    ChunkType type;
    int starting_line;
    vector<string> lines;
};