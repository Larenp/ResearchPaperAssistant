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

  for (const Chunk &chunk : chunks) {
    VectorEntry entry;
    entry.chunk = chunk;
    entry.embedding = embeddingGenerator.generate(chunk);
    database.push_back(entry);
  }

  std::cout << "Indexed " << database.size() << " chunks.\n";

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
  PromptBuilder builder;
  std::string prompt = builder.build(question, results);

  // Display results

  LLMClient llm;

  std::cout << "\nGenerating answer...\n\n";

  std::string answer = llm.generate(prompt);

  std::cout << answer << std::endl;

  return 0;
}