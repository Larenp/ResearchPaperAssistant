#ifndef PDFPARSER_H
#define PDFPARSER_H

#include <string>
#include <vector>

#include "../models/Page.h"

class PDFParser {
public:
  std::vector<Page> extractPages(std::string pdfPath);
};

#endif