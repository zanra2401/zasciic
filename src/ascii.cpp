#include "ascii.hpp"
#include "typeData.hpp"
#include <cmath>
#include <string_view>
#include <cstring>
#include <string>

Asciic::Asciic(const grayScalePixels_t &grayScalePixels_p, const int w, const int h) 
  : grayScalePixels(grayScalePixels_p), w(w), h(h) {
  asciiChars = {'@', '%', '#', '*', '+', '=', '-', ':', '.', ' '};
}

void Asciic::printAscii(bool inverted, bool colored) {  
  for(int y = 0; y < h; y++) {
    for(int x = 0; x < w; x++) {
      std::cout << getChar(grayScalePixels[y][x], inverted, colored);
    }
    std::cout << std::endl;
  }
}

void Asciic::generateANSIIColor(Color_s *colors) {
  int sizeChars = asciiChars.size();
  colors_map.push_back(colors[0]);
  for (int f = 1; f < (sizeChars - 1); f++) {
      float factor = (float) f/sizeChars;
      colors_map.push_back(lerp(colors[0], colors[1], factor));
  }
  colors_map.push_back(colors[1]);
}


std::string Asciic::getChar(int brightness, bool inverted, bool colored) {
  char target_char;
  Color_s* color;
  int idx = floor(brightness * (asciiChars.size() - 1) / 255);
  if(inverted) {
    int inv_idx = std::abs(static_cast<int>(idx - (asciiChars.size() - 1)));
    target_char = asciiChars[inv_idx];
    color = getColor(inv_idx);
  } else {
    target_char = asciiChars[idx];
    color = getColor(idx);
  }

  if (colored) {
    std::stringstream ss;
        
    // Gabungkan ANSI Code + RGB + Karakter + ANSI Reset
    // Format: \033[38;2;R;G;Bm[KARAKTER]\033[0m
    ss << "\033[38;2;" 
       << color->r << ";" 
       << color->g << ";" 
       << color->b << "m" 
       << target_char 
       << "\033[0m";
    return ss.str();
  } else {
    return std::string(1, target_char);
  }
}


// v1 + (v2 - v1) * t[factor]
Color_s Asciic::lerp(Color_s &color1, Color_s &color2, float t) {
  Color_s newColor; 
  newColor.r = color1.r + (color2.r - color1.r) * t;
  newColor.g = color1.g + (color2.g - color1.g) * t;
  newColor.b = color1.b + (color2.b - color1.b) * t;
  return newColor;
}

Color_s* Asciic::getColor(int index) {
  return &colors_map[index];
}

Color_s* Asciic::colorParser(const char *colors[2]) {
  Color_s start;
  Color_s end;
  
  for (int i = 0; i < 2; i++) {
    char channel[20];
    int ic = 0;
    std::vector<int> channels;
    std::string_view sv = colors[i];
    for (const char &c : sv) {
        if (c != ',' || &c == &sv.back()) {
          channel[ic] = c;
          ic += 1;
          if (&c == &sv.back()) {
            ic = 0;
            channels.push_back(std::stoi(channel));
            std::memset(channel, 0, sizeof(channel));
          }
        } else if (c == ',') {
          ic = 0;
          channels.push_back(std::stoi(channel));
          std::memset(channel, 0, sizeof(channel));
        }

    }
    if (channels.size() != 3) {
      std::cerr << "Error argument -c";
      std::cout << channels.size() << std::endl;
      std::exit(-1);
    }
    if (i == 0) {
      start.r = channels[0];
      start.g = channels[1];
      start.b = channels[2];
    } else {
      end.r = channels[0];
      end.g = channels[1];
      end.b = channels[2];
    }
  }

  Color_s *colorsRes = new Color_s[2];
  colorsRes[0] = start;
  colorsRes[1] = end;
  return colorsRes;
}

