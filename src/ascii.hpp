#pragma once
#include "typeData.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <string_view>
#include <cstring>
#include <iostream>
#include <sstream>

class Asciic {
  private:
    std::vector<std::string> asciiChars;
    int w;
    int h;
    std::vector<Color_s> colors_map;
    int idx_hist;

    const grayScalePixels_t& grayScalePixels;
  public:
    Asciic(const grayScalePixels_t &grayScalePixels_p, int w, int h);
    void setChars(const std::string chars);
    std::string getChar(int brightness, bool inverted, bool colored);
    void printAscii(bool inverted, bool colored, std::string_view);
    void generateANSIIColor(Color_s *colors);
    Color_s* colorParser(const char *colors[2]);
    Color_s lerp(Color_s &color1, Color_s &color2, float t);
    Color_s* getColor(int index);
    void writeToFile(std::ofstream& ofs, std::string_view file_name, std::string string_to_write);
};


