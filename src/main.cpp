#include <iostream>

#include "chunk/Chunker.h"
#include "embedding/EmbeddingGenerator.h"
#include "pdf/PDFParser.h"
#include "text/TextCleaner.h"

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

  // Generate embedding for the first chunk
  if (!chunks.empty()) {
    Embedding embedding = embeddingGenerator.generate(chunks[0]);

    std::cout << "Embedding size: " << embedding.values.size() << std::endl;
  }

  // Print all chunks
  for (int i = 0; i < chunks.size(); i++) {
    std::cout << "Chunk " << i + 1 << std::endl;
    std::cout << "Text: " << chunks[i].text << std::endl;
    std::cout << "Page: " << chunks[i].page << std::endl;
    std::cout << "Chunk ID: " << chunks[i].chunkId << std::endl;
    std::cout << "Paper: " << chunks[i].paperName << std::endl;
    std::cout << std::endl;
  }

  return 0;
}