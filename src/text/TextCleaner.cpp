#include "TextCleaner.h"

#include <sstream>

std::string TextCleaner::clean(std::string text)
{
    std::stringstream ss(text);

    std::string line;
    std::string cleanedText = "";

    bool previousLineBlank = false;

    while (getline(ss, line))
    {
        if (line.empty())
        {
            if (!previousLineBlank)
            {
                cleanedText += "\n";
                previousLineBlank = true;
            }
        }
        else
        {
            cleanedText += line;
            cleanedText += "\n";

            previousLineBlank = false;
        }
    }

    return cleanedText;
}