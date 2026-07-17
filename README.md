# zasciic

**zasciic** is a command-line tool that converts images into ASCII art with various customization options like resizing, inverting colors, and applying custom color gradients.

## Build Instructions

This project uses CMake as its build system. To compile `zasciic`, follow these steps:

### Requirements
- CMake
- A modern C++ compiler

### Compilation

1. **Configure the project:**
   ```bash
   cmake -B build
   ```

2. **Build the project:**
   ```bash
   cmake --build build
   ```

3. **Executable:**
   After a successful build, the executable `zasciic` (or `zasciic.exe` on Windows) will be located in the `build` directory (e.g., `./build/zasciic.exe`).

## Basic Usage

Run the executable from your terminal. The basic required argument is `-i` followed by the path to your input image.

```bash
./build/zasciic -i path/to/your/image.jpg
```

### Options

- **`-i [image_path]`** : Path to the input image. (Required)
- **`-w [width]`** : Target width for resizing the image.
- **`-s [scale]`** : Scale factor for resizing.
- **`-inv`** : Invert the ASCII characters (useful depending on your terminal background).
- **`-c [color1] [color2]`** : Apply a color gradient from `color1` to `color2`. Colors must be specified in RGB format without spaces, e.g., `0,0,0 255,255,255`.
- **`-of [output_file]`** : Save the ASCII art output to the specified text file.
- **`-chars [characters]`** : Use a custom string of ASCII characters for generating the art (ordered from darkest to lightest).
- **`-h` / `--help`** : Show the help message and options. *(Note: Help flag is available on the `stable` branch)*

### Examples

**Basic Conversion:**
```bash
./build/zasciic -i image.png
```

**Resize and Invert:**
```bash
./build/zasciic -i image.png -w 100 -inv
```

**Apply Color Gradient and Save to File:**
```bash
./build/zasciic -i image.png -c 255,0,0 0,0,255 -of output.txt
```
