#pragma once
#include <vector>
#include "typeData.hpp"

class Asciic {
  private:
    std::vector<char> asciiChars;
    int w;
    int h;

    const grayScalePixels_t& grayScalePixels;
  public:
    Asciic(const grayScalePixels_t &grayScalePixels_p, int w, int h);
    char getChar(int brightness, bool inverted);
    void printAscii(bool inverted = false);
};

