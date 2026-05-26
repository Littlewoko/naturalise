#pragma once
#include <vector>
#include <string>

using namespace std;

enum class ChunkType {
    CommentBlock,
    Other
};

enum class ViolationLevel {
    WARN,
    ERROR
};

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