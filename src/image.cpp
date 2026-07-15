#include "image.hpp"

Image::Image() {}

void Image::load(const std::string &path) {
    if (!std::filesystem::exists(path)) {
      std::cerr << "Error: Gambar Tidak ditemukan" << std::endl;
      std::exit(-1);
    }

    pixels = stbi_load(path.c_str(), &w, &h, &c, 0);
    aspect = (double)h / (double)w;

    if (!pixels) {
      std::cerr << "Error: Image Error" << std::endl;
      std::exit(-1);
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
  if (c <= 2 && c >= 1) {
    for(int y = 0; y < h; y++) {
      rowPixels_t rowPixels;
      for(int x = 0; x < w; x++) {
        int index = (y * w + x) * c;
        rowPixels.push_back((int) (pixels[index]));
      }
      grayScalePixels.push_back(rowPixels);
    }
  } else {     
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
  }
  stbi_image_free(const_cast<unsigned char*>(pixels));
}

void Image::resizeGrayScale(int newWidth, double scale) {
  int newHeight = (int)(aspect * newWidth * scale);
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
