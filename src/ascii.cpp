#include "ascii.hpp"

Asciic::Asciic(const grayScalePixels_t &grayScalePixels_p, const int w, const int h) 
  : grayScalePixels(grayScalePixels_p), w(w), h(h) {
  asciiChars = {"@", "%", "#", "*", "+", "=", "-", ":", ".", " "};
}

void Asciic::setChars(const std::string chars) {
    asciiChars.clear(); // Lebih ringkas daripada .erase(begin, end)

    // Melakukan parsing string UTF-8 secara manual per karakter
    for (size_t i = 0; i < chars.length(); ) {
        size_t len = 1;
        unsigned char c = chars[i];
        
        // Menentukan panjang byte karakter UTF-8 berdasarkan leading bits
        if (c >= 0xf0) len = 4;
        else if (c >= 0xe0) len = 3;
        else if (c >= 0xc0) len = 2;
        
        if (i + len <= chars.length()) {
            asciiChars.push_back(chars.substr(i, len));
        }
        i += len;
    }
}

void Asciic::printAscii(bool inverted, bool colored, std::string_view file_name) {
    std::stringstream ascii_string;
    bool save_to_file = !file_name.empty();

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            std::string string_to_write = getChar(grayScalePixels[y][x], inverted, colored);
            
            std::cout << string_to_write;
            
            if (save_to_file) {
                ascii_string << string_to_write;
            }
        }
        std::cout << std::endl;
        if (save_to_file) {
            ascii_string << std::endl;
        }
    }

    if (save_to_file) {
        ascii_string << "\033[0m";
        std::ofstream ofs;
        writeToFile(ofs, file_name, ascii_string.str());
        ofs.close();
    }
}

// Perbaikan nama class (Asciic) dan penambahan referensi (&)
void Asciic::writeToFile(std::ofstream& ofs, std::string_view file_name, std::string string_to_write) {
    // Konversi string_view ke std::string agar bisa dibaca oleh .open()
    ofs.open(std::string(file_name), std::ios::out | std::ios::trunc);
    if (ofs.is_open()) {
        ofs << string_to_write;
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
  std::string target_char;
  Color_s* color;
  int idx = floor(brightness * (asciiChars.size() - 1) / 255);
  if(inverted) {
    idx = std::abs(static_cast<int>(idx - (asciiChars.size() - 1)));
    target_char = asciiChars[idx];
    color = getColor(idx);
  } else {
    target_char = asciiChars[idx];
    color = getColor(idx);
  } 

  if (colored) {
    std::stringstream ss;
        
    // Gabungkan ANSI Code + RGB + Karakter + ANSI Reset
    // Format: \033[38;2;R;G;Bm[KARAKTER]\033[0m
    if (idx_hist != idx && target_char != " ") {
      ss << "\033[38;2;" 
         << color->r << ";" 
         << color->g << ";" 
         << color->b << "m";
      idx_hist = idx;
    }
    ss << target_char;
    return ss.str();
  } else {
    return target_char;
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

