#pragma once
#include "image.hpp"    // Gunakan .hpp, bukan .cpp agar tidak terjadi double-declaration
#include "ascii.hpp"
#include "typeData.hpp"

class CommandCenter {
  private:
    int argc;
    const char** argv;  // Menggantikan const char *&commands[] yang ilegal
    
    // Gunakan pointer atau alokasikan secara dinamis karena 'img' dan 'ascii'
    // membutuhkan parameter di constructor-nya (tidak punya default constructor)
    Image* img;
    Asciic* ascii;

    // Variabel untuk menyimpan konfigurasi dari argumen user
    std::string inputPath = "";
    int targetWidth = -1; // -1 artinya opsional (tidak di-resize)
    bool isInverted = false;
    const char *colors[2] = {nullptr, nullptr};
    bool colored = false;

  public:
    CommandCenter(int argc, const char** argv);
    ~CommandCenter(); // Destructor untuk membersihkan pointer
    
    void parseArguments(); // Fungsi baru khusus untuk membaca input acak
    void processCommand();
};
