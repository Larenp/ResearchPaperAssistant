#include "PromptBuilder.h"

#include <sstream>

std::string PromptBuilder::build(const std::string &question,
                                 const std::vector<VectorEntry> &context) {

  std::stringstream prompt;

  prompt << "You are a helpful research assistant.\n\n";

  prompt << "Answer the question ONLY using the provided context.\n";
  prompt << "If the answer cannot be found in the context, say so.\n\n";
  prompt << "Rules:\n";
  prompt << "1. Do NOT use your own knowledge.\n";
  prompt << "2. Do NOT make assumptions.\n";
  prompt
      << "3. If the answer is not explicitly present in the context, reply "
         "exactly: 'I could not find the answer in the provided document.'\n";
  prompt << "4. Do not answer questions unrelated to the document.\n\n";

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