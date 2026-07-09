#ifndef PROMPTBUILDER_H
#define PROMPTBUILDER_H

#include <string>
#include <vector>

#include "../models/VectorEntry.h"

class PromptBuilder {
public:
  std::string build(const std::string &question,
                    const std::vector<VectorEntry> &context);
};

#endif
