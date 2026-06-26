#pragma once
#include <vector>

struct Pixel_s {
  int r;
  int g;
  int b;
};

typedef std::vector<int> rowPixels_t;
typedef std::vector<rowPixels_t> grayScalePixels_t;
