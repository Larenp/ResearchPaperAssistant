#include "EmbeddingGenerator.h"

#include <array>
#include <cstdio>
#include <memory>
#include <string>

Embedding EmbeddingGenerator::generate(const Chunk &chunk) {
  Embedding embedding;

  std::string command =
      "../src/python/.venv/bin/python ../src/python/embedding_service.py \"" +
      chunk.text + "\"";
  std::array<char, 256> buffer;

  FILE *pipe = popen(command.c_str(), "r");

  if (!pipe) {
    return embedding;
  }

  while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
    std::string line(buffer.data());

    if (!line.empty() && line.back() == '\n') {
      line.pop_back();
    }

    embedding.values.push_back(std::stof(line));
  }

  pclose(pipe);

  return embedding;
}