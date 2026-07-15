#pragma once
#include <string>
#include <vector>
#include "typeData.hpp"
#include "stb_image.h"
#include <string>
#include <iostream>
#include <cstring>
#include <filesystem>
#include <exception>

class Image {
  private:    
    int w;
    int h;
    int c;
    double aspect;

    const unsigned char *pixels;
    grayScalePixels_t grayScalePixels;

  public:
    Image();
    ~Image();
    void load(const std::string &path);
    void resizeGrayScale(int newWidth, double scale = 0.5);
    void toGrayScalePixels();
    void debug();
    void debugGrayScale();

    const grayScalePixels_t& getGrayScalePixels() const;

    int getWidth() const ;
    int toGrayScale(Pixel_s &pixel);
    int getHeight() const;
};
