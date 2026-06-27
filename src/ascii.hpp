#pragma once
#include <vector>
#include "typeData.hpp"
#include <string>

class Asciic {
  private:
    std::vector<char> asciiChars;
    int w;
    int h;
    std::vector<Color_s> colors_map;

    const grayScalePixels_t& grayScalePixels;
  public:
    Asciic(const grayScalePixels_t &grayScalePixels_p, int w, int h);
    std::string getChar(int brightness, bool inverted, bool colored);
    void printAscii(bool inverted = false, bool colored = false);
    void generateANSIIColor(Color_s *colors);
    Color_s* colorParser(const char *colors[2]);
    Color_s lerp(Color_s &color1, Color_s &color2, float t);
    Color_s* getColor(int index);
};

