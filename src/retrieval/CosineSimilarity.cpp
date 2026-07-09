#include "CosineSimilarity.h"

#include <cmath>

double CosineSimilarity::calculate(const Embedding &a, const Embedding &b) {
  double dotProduct = 0.0;
  double magnitudeA = 0.0;
  double magnitudeB = 0.0;

  for (int i = 0; i < a.values.size(); i++) {
    dotProduct += a.values[i] * b.values[i];

    magnitudeA += a.values[i] * a.values[i];
    magnitudeB += b.values[i] * b.values[i];
  }

  magnitudeA = sqrt(magnitudeA);
  magnitudeB = sqrt(magnitudeB);

  if (magnitudeA == 0 || magnitudeB == 0) {
    return 0.0;
  }

  return dotProduct / (magnitudeA * magnitudeB);
}