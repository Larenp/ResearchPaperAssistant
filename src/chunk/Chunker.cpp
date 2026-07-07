#include "Chunker.h"

std::vector<Chunk> Chunker::split(std::string text) {
  std::vector<Chunk> chunks;

  int chunkSize = 50;
  int overlap = 10;

  int start = 0;

  while (start < text.length()) {
    int end = start + chunkSize;

    if (end > text.length()) {
      end = text.length();
    }

    int splitPosition = text.find_last_of(' ', end);

    if (splitPosition == std::string::npos || splitPosition <= start) {
      splitPosition = end;
    }

    Chunk chunk;

    chunk.text = text.substr(start, splitPosition - start);
    chunk.page = 0;
    chunk.chunkId = chunks.size() + 1;
    chunk.paperName = "paper.pdf";

    chunks.push_back(chunk);

    start = splitPosition + 1;
  }

  return chunks;
}