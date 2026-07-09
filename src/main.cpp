#include "chunk/Chunker.h"
#include "embedding/EmbeddingGenerator.h"
#include "models/VectorEntry.h"
#include "pdf/PDFParser.h"
#include "text/TextCleaner.h"
#include <iostream>

int main() {
  PDFParser parser;
  TextCleaner cleaner;
  Chunker chunker;
  EmbeddingGenerator embeddingGenerator;

  // Extract pages from PDF
  std::vector<Page> pages = parser.extractPages("../paper.pdf");

  // Clean text
  pages = cleaner.clean(pages);

  // Split into chunks
  std::vector<Chunk> chunks = chunker.split(pages);

  // Generate embeddings for all chunks
  std::vector<VectorEntry> database;

  for (const Chunk &chunk : chunks) {
    VectorEntry entry;

    entry.chunk = chunk;
    entry.embedding = embeddingGenerator.generate(chunk);

    database.push_back(entry);
  }

  std::cout << "Total Chunks: " << chunks.size() << std::endl;
  std::cout << "Total Vector Entries: " << database.size() << std::endl;

  // Verify each embedding
  for (const auto &entry : database) {
    std::cout << "Chunk " << entry.chunk.chunkId
              << " -> Embedding size: " << entry.embedding.values.size()
              << std::endl;
  }

  return 0;
}