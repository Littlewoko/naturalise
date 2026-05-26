#include "chunker.h"

using namespace std;

void Chunker::emit_chunk(vector<Chunk> &chunks, ChunkType type, int start_line, vector<string> &buffer) {
    if (buffer.empty()) return;
    
    Chunk chunk;
    chunk.starting_line = start_line;
    chunk.lines = std::move(buffer); // steals the buffer and clears it
    chunk.type = type;

    chunks.push_back(chunk);
}

vector<Chunk> Chunker::chunk(istream &input_stream) {
    vector<string> buffer;
    vector<Chunk> res;
    
    string line;
    while(getline(input_stream, line)) {
        buffer.push_back(line);
    }

    emit_chunk(res, ChunkType::CommentBlock, 1, buffer);

    return res;
}