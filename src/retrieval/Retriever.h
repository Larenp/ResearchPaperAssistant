#ifndef RETRIEVER_H
#define RETRIEVER_H

#include <vector>

#include "../models/VectorEntry.h"

class Retriever {
public:
  std::vector<VectorEntry> retrieve(const Embedding &queryEmbedding,
                                    const std::vector<VectorEntry> &database,
                                    int topK);
};

#endif