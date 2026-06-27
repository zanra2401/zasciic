#include "commandCenter.hpp"
#include <iostream>
#include <string>
#include "image.cpp"
#include "ascii.cpp"

CommandCenter::CommandCenter(int argc, const char** argv) 
    : argc(argc), argv(argv), img(nullptr), ascii(nullptr) {}

CommandCenter::~CommandCenter() {
    delete img;
    delete ascii;
}

void CommandCenter::parseArguments() {
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        if (arg == "-i" && i + 1 < argc) {
            inputPath = argv[++i]; // Ambil argumen setelahnya sebagai path file
        } 
        else if (arg == "-w" && i + 1 < argc) {
            targetWidth = std::stoi(argv[++i]); // Ambil argumen setelahnya, ubah ke int
        } 
        else if (arg == "-inv") {
            isInverted = true;
        } else if (arg == "-c" && i + 2 < argc) {
          colored = true;
          colors[0] = argv[++i];
          colors[1] = argv[++i];
        }
    }
}

void CommandCenter::processCommand() {
    // 1. Baca semua argumen acak dari user
    parseArguments();

    // 2. VALIDASI SYARAT ATURAN V1
    
    // Syarat 1: Wajib ada input gambar
    if (inputPath.empty()) {
        std::cerr << "Error: Flag '-i [input_gambar]' wajib diisi!\n";
        return;
    }

    // Syarat 2: Jika ada flag -w, pastikan ukurannya valid
    if (targetWidth != -1 && targetWidth <= 0) {
        std::cerr << "Error: Ukuran width (-w) harus lebih besar dari 0!\n";
        return;
    }

    // 3. JALANKAN ALGORITMA SESUAI URUTAN EKSEKUSI (Bukan urutan ketik user)
    
    img = new Image();
    img->load(inputPath);
    img->toGrayScalePixels();

    // Cek apakah user meminta resize opsional
    if (targetWidth != -1) {
        img->resizeGrayScale(targetWidth); 
    } else {
        img->resizeGrayScale(120);
    }

    // Bangun objek Asciic setelah pengolahan gambar selesai (Grayscale & Resize)
    ascii = new Asciic(img->getGrayScalePixels(), img->getWidth(), img->getHeight());
    
    // Syarat 3: Jika flag -inv aktif, lakukan invert warna di sini
    if (colored) {
      if (colors[0] != nullptr && colors[1] != nullptr) {
        Color_s *colors_st = ascii->colorParser(colors);
        ascii->generateANSIIColor(colors_st);
      } else {
        std::cerr 
          << "Error: Color args is not valid \n" 
          << "Usage: -c [color1 color2] \n"
          << "Example: -c 0,0,0 255,255,255"
          << std::endl;
        std::exit(-1);
      }
    }

    if (isInverted) {
        ascii->printAscii(true, colored);
    } else {
        ascii->printAscii(false, colored);
    }

}
