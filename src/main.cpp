#include <iostream>

#include "pdf/PDFParser.h"
#include "text/TextCleaner.h"
#include "chunk/Chunker.h"

int main()
{
    PDFParser parser;
    TextCleaner cleaner;
    Chunker chunker;

    std::string text = parser.extractText("../paper.pdf");

    std::string cleanText = cleaner.clean(text);

    std::vector<std::string> chunks = chunker.split(cleanText);

    for (int i = 0; i < chunks.size(); i++)
    {
        std::cout << "Chunk " << i + 1 << ":\n";
        std::cout << chunks[i] << "\n\n";
    }

    return 0;
}