#include "commandCenter.hpp"

CommandCenter::CommandCenter(int argc, const char** argv) 
    : argc(argc), argv(argv), img(nullptr), ascii(nullptr) {}

CommandCenter::~CommandCenter() {
    delete ascii;
    delete img;
}

void CommandCenter::printHelp() {
    std::cout << "Usage: zasciic [OPTIONS]\n"
              << "Options:\n"
              << "  -i [image_path]        Input image path (Required)\n"
              << "  -w [width]             Target width for resizing\n"
              << "  -s [scale]             Scale factor for resizing\n"
              << "  -inv                   Invert ASCII colors\n"
              << "  -c [color1] [color2]   Apply color gradient (e.g. 0,0,0 255,255,255)\n"
              << "  -of [output_file]      Save output to a file\n"
              << "  -chars [characters]    Custom ASCII characters to use\n"
              << "  -h, --help             Show this help message\n";
    std::exit(0);
}

void CommandCenter::parseArguments() {
    if (argc <= 1) {
        printHelp();
    }

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
        } else if (arg == "-of" && i + 1 < argc) {
          out_file_name = std::string_view(argv[++i]);
        }else if (arg == "-s" && i + 1 < argc) {
          scale = std::stod(argv[++i]);
        }else if (arg == "-chars" && i + 1 < argc) {
          asciiChars = argv[++i];
        } else if (arg == "-h" || arg == "--help") {
          printHelp();
        } else {
          std::cerr << argv[i] << " is not recognized as a arguments. Use -h or --help for usage.\n";
          std::exit(-1);
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
        if (scale != -1) {
          img->resizeGrayScale(targetWidth, scale);
        } else {
          img->resizeGrayScale(targetWidth);
        }
    } else {
        if (scale != -1) {
          img->resizeGrayScale(120, scale);
        } else {
          img->resizeGrayScale(120);
        }
    }

    // Bangun objek Asciic setelah pengolahan gambar selesai (Grayscale & Resize)
    ascii = new Asciic(img->getGrayScalePixels(), img->getWidth(), img->getHeight());

    if (!asciiChars.empty()) {
      ascii->setChars(asciiChars);
    }
    
    
    // Syarat 3: Jika flag -inv aktif, lakukan invert warna di sini
    if (colored) {
      if (colors[0] != nullptr && colors[1] != nullptr) {
        Color_s *colors_st = ascii->colorParser(colors);
        ascii->generateANSIIColor(colors_st);
        delete[] colors_st;
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
        ascii->printAscii(true, colored, out_file_name);
    } else {
        ascii->printAscii(false, colored, out_file_name);
    }

}
