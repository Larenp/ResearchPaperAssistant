#include <iostream>
#include "pdf/PDFParser.h"

int main()
{
    PDFParser parser;

    std::string text = parser.extractText("../paper.pdf");

    std::cout << text << std::endl;

    return 0;
}