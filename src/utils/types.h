#pragma once
#include <vector>
#include <string>

using namespace std;

enum class ChunkType {
    CommentBlock,
    Other
};

struct Violation {
    int line_number;
    string message;
};

struct Chunk {
    ChunkType type;
    int starting_line;
    vector<string> lines;
};