#include "PromptBuilder.h"

#include <sstream>

std::string PromptBuilder::build(const std::string &question,
                                 const std::vector<VectorEntry> &context) {

  std::stringstream prompt;

  prompt << "You are a helpful research assistant.\n\n";

  prompt << "Answer the question ONLY using the provided context.\n";
  prompt << "If the answer cannot be found in the context, say so.\n\n";

  prompt << "Context:\n\n";

  for (const auto &entry : context) {
    prompt << "Chunk " << entry.chunk.chunkId << " (Page " << entry.chunk.page
           << ")\n";

    prompt << entry.chunk.text << "\n\n";
  }

  prompt << "Question:\n";
  prompt << question << "\n\n";

  prompt << "Answer:\n";

  return prompt.str();
}