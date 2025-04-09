#include <stdlib.h>

#include "chunk.h"

void initChunk(Chunk* chunk) {
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = {};
    chunk->lines = {};
    initValueArray(chunk->constants);
}


void freeChunk(Chunk* chunk) {
    chunk->code.clear();         // Removes all elements but keeps allocated capacity
    chunk->code.shrink_to_fit(); // Frees excess memory
    chunk->lines.clear();         // Removes all elements but keeps allocated capacity
    chunk->lines.shrink_to_fit(); // Frees excess memory
    freeValueArray(chunk->constants);
    initChunk(chunk);
    // chunk.constants.clear();         // Remove all constants
    // chunk.constants.shrink_to_fit(); // Free unused memory
}

void writeChunk(Chunk* chunk, uint8_t byte , int line) {
    chunk->code.push_back(static_cast<uint8_t>(byte));
    chunk->lines.push_back(line);
    chunk->count++;
    chunk->capacity++;
}

int addConstant(Chunk* chunk, Value value) {
    writeValueArray(chunk->constants, value);
    return chunk->constants.count - 1; // index appended
}

