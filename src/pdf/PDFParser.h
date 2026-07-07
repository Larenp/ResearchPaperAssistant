#ifndef PDFPARSER_H
#define PDFPARSER_H

#include <string>

class PDFParser {
public:
  std::string extractText(std::string pdfPath);
};

#endif