#ifndef VECTORENTRY_H
#define VECTORENTRY_H

#include "Chunk.h"
#include "Embedding.h"

struct VectorEntry {
  Chunk chunk;
  Embedding embedding;
};

#endif