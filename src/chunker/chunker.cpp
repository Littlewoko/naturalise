#include "chunker.h"

using namespace std;

bool Chunker::update_state(ParserState &state, string &line) {
    if (line.empty() || (line[0] == '*' || line.find_first_not_of(" \t\v\f") == string::npos)) {
        // line is empty, starts with a * or is only whitespace

        if (state != ParserState::ReadingComment) {
            state = ParserState::ReadingComment;
            return true;
        }
    } else {
        // everything else
        if (state != ParserState::ReadingOther) {
            state = ParserState::ReadingOther;
            return true;
        }
    }

    return false;
}

void Chunker::emit_chunk(vector<Chunk> &chunks, ChunkType type, int start_line, vector<string> &buffer) {
    if (buffer.empty()) return;
    
    Chunk chunk;
    chunk.starting_line = start_line;
    chunk.lines = std::move(buffer); // steals the buffer and clears it
    chunk.type = type;

    chunks.push_back(chunk);
}

vector<Chunk> Chunker::chunk(istream &input_stream) {
    ParserState state = ParserState::Initial;

    vector<string> buffer;
    vector<Chunk> res;
    
    int line_number = 1;
    string line;
    while(getline(input_stream, line)) {
        ParserState prevState = state;
        bool updated = update_state(state, line);

        if (updated) {
            ChunkType type = prevState == ParserState::ReadingComment ? ChunkType::CommentBlock : ChunkType::Other;
            int starting_linenumber = line_number;

            line_number += buffer.size();

            emit_chunk(res, type, starting_linenumber, buffer);
        }

        buffer.push_back(line);
    }

    if (state != ParserState::Initial) { // entered the loop
        ChunkType type = state == ParserState::ReadingComment ? ChunkType::CommentBlock : ChunkType::Other;
        emit_chunk(res, type, line_number, buffer);
    }

    return res;
}