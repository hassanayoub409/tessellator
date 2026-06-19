# The Tessellator

A C++ interactive application that lets you generate and explore mathematical tessellations with custom colors and sizes — built with SFML 2.1.

![Language](https://img.shields.io/badge/Language-C%2B%2B11-blue)
![Library](https://img.shields.io/badge/Library-SFML%202.1-green)
![Platform](https://img.shields.io/badge/Platform-macOS%20%7C%20Windows%20%7C%20Linux-lightgrey)

---

## Features

- **6 Tessellation types** — Square, Triangle, Hexagon, Voronoi Cells, Sierpinski Triangle, Penrose Tiling
- **Custom color picker** — RGB sliders to set the tile color
- **Custom size control** — Slider to adjust tile size
- **Animated intro screen** with background music
- **Clean menu navigation** with mouse interaction

---

## Screenshots

**Landing Screen
![Landing Screen](https://github.com/hassanayoub409/tessellator/blob/1a94a324ea42fe01398cdbfb06966c810a9fcc69/main.png)

**Shape Selection Screen
![Shape Selection Screen](https://github.com/hassanayoub409/tessellator/blob/1a94a324ea42fe01398cdbfb06966c810a9fcc69/options.png)

**Penrose Tiling Example
![Penrose Tiling Example](https://github.com/hassanayoub409/tessellator/blob/1a94a324ea42fe01398cdbfb06966c810a9fcc69/penrose.png)

**Voronoi Cells Example
![Voronoi Cells Example](https://github.com/hassanayoub409/tessellator/blob/1a94a324ea42fe01398cdbfb06966c810a9fcc69/varanoi.png)

---

## Prerequisites

Before building, you need **SFML 2.1** installed or downloaded for your platform.

| Platform | Download |
|----------|----------|
| macOS    | [SFML 2.1 for macOS](https://www.sfml-dev.org/download/sfml/2.1/) |
| Windows  | [SFML 2.1 for Windows](https://www.sfml-dev.org/download/sfml/2.1/) |
| Linux    | `sudo apt-get install libsfml-dev` |

---

## Building the Project

### macOS / Linux

1. Clone the repository:
   ```bash
   git clone https://github.com/hassanayoub409/tessellator.git
   cd tessellator
   ```

2. Place your downloaded SFML 2.1 folder in the project root and rename it `SFML-2.1/`, so the structure looks like:
   ```
   The-Tessellator/
   ├── SFML-2.1/
   │   ├── include/
   │   └── lib/
   ├── src/
   ├── assets/
   └── README.md
   ```

3. Navigate into `src/` and compile:
   ```bash
   cd src
   g++ -std=c++11 main.cpp Menu.cpp FrameShape.cpp Slider.cpp Triangle.cpp \
       Button.cpp Square.cpp Hexagon.cpp Varanoi.cpp Sierpinski.cpp Penrose.cpp \
       -I../SFML-2.1/include \
       -o main \
       -L../SFML-2.1/lib \
       -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
   ```

4. Run the application:
   ```bash
   ./main
   ```

---

### Windows (MinGW)

1. Clone the repository and download the **GCC MinGW** version of SFML 2.1 from the link above.

2. Place it in the project root as `SFML-2.1/`.

3. Open a terminal (e.g. Git Bash or MSYS2) in the `src/` folder and compile:
   ```bash
   g++ -std=c++11 main.cpp Menu.cpp FrameShape.cpp Slider.cpp Triangle.cpp \
       Button.cpp Square.cpp Hexagon.cpp Varanoi.cpp Sierpinski.cpp Penrose.cpp \
       -I../SFML-2.1/include \
       -o main.exe \
       -L../SFML-2.1/lib \
       -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
   ```

4. Copy the SFML `.dll` files from `SFML-2.1/bin/` into your `src/` folder, then run:
   ```bash
   ./main.exe
   ```

---

### Windows (Visual Studio)

1. Open Visual Studio and create a new **Empty C++ Project**.
2. Add all `.cpp` files from the `src/` folder to the project.
3. Go to **Project → Properties** and configure:
   - **C/C++ → Additional Include Directories** → path to `SFML-2.1/include`
   - **Linker → Additional Library Directories** → path to `SFML-2.1/lib`
   - **Linker → Additional Dependencies** → `sfml-graphics.lib; sfml-window.lib; sfml-system.lib; sfml-audio.lib`
4. Copy the SFML `.dll` files from `SFML-2.1/bin/` next to your executable.
5. Build and run.

---

## Project Structure

```
The-Tessellator/
├── src/
│   ├── main.cpp          # Entry point and application loop
│   ├── Tessellator.h     # Abstract base class
│   ├── Enum.h            # Screen state definitions
│   ├── Menu.h / .cpp     # Main menu
│   ├── Button.h / .cpp   # UI button component
│   ├── Slider.h / .cpp   # UI slider component
│   ├── FrameShape.h/.cpp # Base drawable shape
│   ├── Triangle.h / .cpp # Triangle tessellation
│   ├── Square.h / .cpp   # Square tessellation
│   ├── Hexagon.h / .cpp  # Hexagon tessellation
│   ├── Varanoi.h / .cpp  # Voronoi cell tessellation
│   ├── Sierpinski.h/.cpp # Sierpinski triangle fractal
│   └── Penrose.h / .cpp  # Penrose tiling
├── assets/
│   ├── images/           # Tile preview images and background
│   ├── fonts/            # Application fonts
│   └── music/            # Background music (Vivaldi)
└── README.md
```

---

## Author

**Hassan Ayoub** — December 2024

---

## License

This project is for educational and personal use.  
SFML is licensed under the [zlib/png license](https://www.sfml-dev.org/license.php).
