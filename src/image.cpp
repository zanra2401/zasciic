#include "image.hpp"
#include "stb_image.h"
#include "exceptionC.cpp"
#include <string>
#include <iostream>
#include <cstring>
#include <filesystem>
#include <exception>
#include "typeData.hpp"

Image::Image() {}

void Image::load(const std::string &path) {
  try {
    if (!std::filesystem::exists(path)) {
      throw NotFoundException(path);
    }

    pixels = stbi_load(path.c_str(), &w, &h, &c, 0);
    aspect = (double)h / (double)w;

    if (!pixels) {
      throw ImageErrorException(pixels);
    }

    if (c != 3) {
      throw NotSupportedException("Right Now This Program only support RGB channels");
    }

  } catch (NotFoundException e) {
    std::cout << "Error not found: " << e.what() << std::endl;
  }
}

void Image::debug() {
  for(int x = 0; x < w * c; x++) {
    for(int y = 0; y < h; y++) {
        std::cout << (int)pixels[y * w + x] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void Image::debugGrayScale() {
  std::cout << "widht: " << grayScalePixels[0].size() << " ";
  std::cout << "heigth: " << grayScalePixels.size();
  std::cout << std::endl;
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      std::cout << grayScalePixels[y][x] << " ";
    }
    std::cout << std::endl;
  }
}

void Image::toGrayScalePixels() {
  for(int y = 0; y < h; y++) {
    rowPixels_t rowPixels;
    for(int x = 0; x < w; x++) {
      Pixel_s pixel;
      int index = (y * w + x) * c;
      pixel.r = pixels[index];
      pixel.g = pixels[index + 1];
      pixel.b = pixels[index + 2];
      int grayScale = toGrayScale(pixel);
      rowPixels.push_back(grayScale);
    }
    grayScalePixels.push_back(rowPixels);
  }
  stbi_image_free(const_cast<unsigned char*>(pixels));
}

void Image::resizeGrayScale(int newWidth) {
  int newHeight = (int)(aspect * newWidth * 0.5);
  double widthScaleFactor =  (double)newWidth / w;
  double heightScaleFactor = (double)newHeight / h;

  grayScalePixels_t newGrayScalePixels;

  for (int y = 0; y < newHeight; y++) {
    rowPixels_t newRowPixels;
    int newY = (int) y / heightScaleFactor;
    for (int x = 0; x < newWidth; x++) {
      int newX = (int) x / widthScaleFactor; 
      newRowPixels.push_back(grayScalePixels[newY][newX]);
    }
    newGrayScalePixels.push_back(newRowPixels);
  }
  grayScalePixels = newGrayScalePixels;
  w = newWidth;
  h = newHeight;
}

const grayScalePixels_t& Image::getGrayScalePixels() const {
  return grayScalePixels;
}

int Image::toGrayScale(Pixel_s &pixel) {
  return int(
      0.299 * pixel.r +
      0.587 * pixel.g +
      0.144 * pixel.b
  );
}

int Image::getWidth() const {
  return w;
}

int Image::getHeight() const {
  return h;
}





