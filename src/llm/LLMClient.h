#ifndef LLMCLIENT_H
#define LLMCLIENT_H

#include <string>

class LLMClient {
public:
  std::string generate(const std::string &prompt);
};

#endif
