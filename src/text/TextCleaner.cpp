#include "TextCleaner.h"

#include <sstream>

std::vector<Page> TextCleaner::clean(std::vector<Page> pages) {
  for (int i = 0; i < pages.size(); i++) {
    std::stringstream ss(pages[i].text);

    std::string line;
    std::string cleanedText = "";

    bool previousLineBlank = false;

    while (getline(ss, line)) {
      if (line.empty()) {
        if (!previousLineBlank) {
          cleanedText += "\n";
          previousLineBlank = true;
        }
      } else {
        cleanedText += line;
        cleanedText += "\n";
        previousLineBlank = false;
      }
    }

    pages[i].text = cleanedText;
  }

  return pages;
}