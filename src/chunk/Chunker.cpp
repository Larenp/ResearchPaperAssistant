#include "Chunker.h"

std::vector<std::string> Chunker::split(std::string text)
{
    std::vector<std::string> chunks;

    int chunkSize = 50;
    int start = 0;

    while (start < text.length())
    {
        int end = start + chunkSize;

        if (end > text.length())
        {
            end = text.length();
        }

        int splitPosition = text.find_last_of(' ', end);

        if (splitPosition == std::string::npos || splitPosition <= start)
        {
            splitPosition = end;
        }

        std::string chunk = text.substr(start, splitPosition - start);

        chunks.push_back(chunk);

        start = splitPosition + 1;
    }

    return chunks;
}