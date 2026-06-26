#pragma once
#include <string>
#include <vector>
#include "typeData.hpp"

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
    void load(const std::string &path);
    void resizeGrayScale(int newWidth);
    void toGrayScalePixels();
    void debug();
    void debugGrayScale();

    const grayScalePixels_t& getGrayScalePixels() const;

    int getWidth() const ;
    int toGrayScale(Pixel_s &pixel);
    int getHeight() const;
};
