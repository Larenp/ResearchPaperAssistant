#ifndef CHUNK_H
#define CHUNK_H

#include <string>

struct Chunk {
  std::string text;
  int page;
  int chunkId;
  std::string paperName;
};

#endif