#ifndef CHUNKER_H
#define CHUNKER_H

#include <string>
#include <vector>

#include "../models/Chunk.h"

class Chunker {
public:
  std::vector<Chunk> split(std::string text);
};

#endif