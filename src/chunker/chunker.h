#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "utils/types.h"

using namespace std;

class Chunker {
public:
    Chunker() = default;

    vector<Chunk> chunk(istream &input_stream);

private:
    enum class ParserState {
        ReadingComment,
    };

    void emit_chunk(vector<Chunk> &chunk, ParserState type, int start_line, vector<string> &buffer);
};