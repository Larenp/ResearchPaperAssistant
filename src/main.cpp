#include <iostream>

#include "chunk/Chunker.h"
#include "pdf/PDFParser.h"
#include "text/TextCleaner.h"

int main() {
  PDFParser parser;
  TextCleaner cleaner;
  Chunker chunker;

  std::string text = parser.extractText("../paper.pdf");

  std::string cleanText = cleaner.clean(text);
  std::vector<Chunk> chunks = chunker.split(cleanText);

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