#include "ascii.hpp"
#include "typeData.hpp"
#include <cmath>

Asciic::Asciic(const grayScalePixels_t &grayScalePixels_p, const int w, const int h) 
  : grayScalePixels(grayScalePixels_p), w(w), h(h) {
  asciiChars = {'@', '%', '#', '*', '+', '=', '-', ':', '.', ' '};
}

char Asciic::getChar(int brightness, bool inverted) {
  if(inverted) {
    return asciiChars[abs(floor(brightness * (asciiChars.size() - 1) / 255) - (asciiChars.size() - 1))];
  }

  return asciiChars[floor(brightness * (asciiChars.size() - 1)) / 255];
}

void Asciic::printAscii(bool inverted) {  
  for(int y = 0; y < h; y++) {
    for(int x = 0; x < w; x++) {
      std::cout << getChar(grayScalePixels[y][x], inverted);
    }
    std::cout << std::endl;
  }
}

