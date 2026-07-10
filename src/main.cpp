#include <iostream>

#include "chunk/Chunker.h"
#include "embedding/EmbeddingGenerator.h"
#include "llm/LLMClient.h"
#include "models/VectorEntry.h"
#include "pdf/PDFParser.h"
#include "prompt/PromptBuilder.h"
#include "retrieval/Retriever.h"
#include "text/TextCleaner.h"

int main() {
  PDFParser parser;
  TextCleaner cleaner;
  Chunker chunker;
  EmbeddingGenerator embeddingGenerator;
  Retriever retriever;

  // Parse, clean and chunk the PDF
  std::vector<Page> pages = parser.extractPages("../paper.pdf");
  pages = cleaner.clean(pages);
  std::vector<Chunk> chunks = chunker.split(pages);

  // Build the vector database
  std::vector<VectorEntry> database;

  int count = 1;

  for (const Chunk &chunk : chunks) {
    std::cout << "Embedding Chunk " << count << "/" << chunks.size()
              << std::endl;

    VectorEntry entry;

    entry.chunk = chunk;
    entry.embedding = embeddingGenerator.generate(chunk);

    database.push_back(entry);

    count++;
  }

  // Read user query
  std::string question;
  std::cout << "\nAsk a question: ";
  std::getline(std::cin, question);

  Chunk queryChunk;
  queryChunk.text = question;
  queryChunk.page = -1;
  queryChunk.chunkId = -1;
  queryChunk.paperName = "Query";

  // Generate query embedding
  Embedding queryEmbedding = embeddingGenerator.generate(queryChunk);

  if (queryEmbedding.values.empty()) {
    std::cout << "Failed to generate query embedding.\n";
    return 1;
  }

  // Retrieve top matching chunks
  std::vector<VectorEntry> results =
      retriever.retrieve(queryEmbedding, database, 3);

  if (results.empty()) {
    std::cout << "No relevant chunks found.\n";
    return 0;
  }

  // Build prompt
  PromptBuilder builder;
  std::string prompt = builder.build(question, results);

  // Generate answer
  LLMClient llm;
  std::string answer = llm.generate(prompt);

  std::cout << "\n" << answer << std::endl;

  return 0;
}