#ifndef CHUNKER_H
#define CHUNKER_H

#include <string>
#include <vector>

class Chunker
{
public:
    std::vector<std::string> split(std::string text);
};

#endif