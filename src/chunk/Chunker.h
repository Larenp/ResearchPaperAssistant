#ifndef CHUNKER_H
#define CHUNKER_H

#include <vector>

#include "../models/Chunk.h"
#include "../models/Page.h"

class Chunker {
public:
  std::vector<Chunk> split(std::vector<Page> pages);
};

#endif