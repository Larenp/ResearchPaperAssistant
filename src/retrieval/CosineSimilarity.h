#ifndef COSINESIMILARITY_H
#define COSINESIMILARITY_H

#include "../models/Embedding.h"

class CosineSimilarity {
public:
  double calculate(const Embedding &a, const Embedding &b);
};

#endif