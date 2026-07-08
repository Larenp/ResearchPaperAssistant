#ifndef TEXTCLEANER_H
#define TEXTCLEANER_H

#include <vector>

#include "../models/Page.h"

class TextCleaner {
public:
  std::vector<Page> clean(std::vector<Page> pages);
};

#endif