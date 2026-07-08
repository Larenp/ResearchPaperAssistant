#ifndef EMBEDDING_GENERATOR_H
#define EMBEDDING_GENERATOR_H

#include "../models/Chunk.h"
#include "../models/Embedding.h"

class EmbeddingGenerator {
public:
  Embedding generate(const Chunk &chunk);
};

#endif