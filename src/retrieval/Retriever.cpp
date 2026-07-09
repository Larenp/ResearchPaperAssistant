#include "Retriever.h"

#include <algorithm>

#include "CosineSimilarity.h"
struct SearchResult {
  VectorEntry entry;
  double score;
};
std::vector<VectorEntry>
Retriever::retrieve(const Embedding &queryEmbedding,
                    const std::vector<VectorEntry> &database, int topK) {
  std::vector<SearchResult> results;

  CosineSimilarity similarity;

  for (const VectorEntry &entry : database) {
    SearchResult result;

    result.entry = entry;

    result.score = similarity.calculate(queryEmbedding, entry.embedding);

    results.push_back(result);
  }
  std::sort(results.begin(), results.end(),
            [](const SearchResult &a, const SearchResult &b) {
              return a.score > b.score;
            });
  std::vector<VectorEntry> topResults;
  for (int i = 0; i < topK && i < results.size(); i++) {
    topResults.push_back(results[i].entry);
  }

  return topResults;
}