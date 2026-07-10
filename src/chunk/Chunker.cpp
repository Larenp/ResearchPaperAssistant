#include "Chunker.h"

std::vector<Chunk> Chunker::split(std::vector<Page> pages) {
  std::vector<Chunk> chunks;

  int chunkSize = 200;

  for (int pageIndex = 0; pageIndex < pages.size(); pageIndex++) {
    std::string text = pages[pageIndex].text;

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
      chunk.page = pages[pageIndex].pageNumber;
      chunk.chunkId = chunks.size() + 1;
      chunk.paperName = "paper.pdf";

      chunks.push_back(chunk);

      start = splitPosition + 1;
    }
  }

  return chunks;
}