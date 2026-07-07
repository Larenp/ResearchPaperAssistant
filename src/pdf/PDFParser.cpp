#include "PDFParser.h"

#include <poppler-document.h>
#include <poppler-page.h>

std::string PDFParser::extractText(std::string pdfPath)
{
    auto document = poppler::document::load_from_file(pdfPath);

    if (!document)
    {
        return "Could not open PDF.";
    }

    std::string result = "";

    int totalPages = document->pages();

    for (int i = 0; i < totalPages; i++)
    {
        auto page = document->create_page(i);

        if (!page)
        {
            continue;
        }

        auto pageText = page->text();

        auto utf8 = pageText.to_utf8();

        std::string text(utf8.begin(), utf8.end());

        result += text;
        result += "\n\n";
    }

    return result;
}