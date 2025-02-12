# TopDown Game Engine *(Rewrite Branch)*

## Overview

This branch contains the complete rewrite of **TopDown Game Engine**, inspired by
[The Cherno's Game Engine series](https://youtube.com/playlist?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT&si=kWuiV_w8-P1DgTe-).
The goal of this rewrite is to build a high-performance, modular, and scalable
game engine from the ground up, following best practices.

<!--
![screenshot-20241109-154218Z-selected](https://github.com/user-attachments/assets/6ee2e0c7-7378-44ad-a144-b2c6917a227d)
-->

<!---
![screenshot-20241120-122706Z-selected](https://github.com/user-attachments/assets/59d7dfb0-8966-49e3-8e78-f8a1c497851d)
-->

![TopDownGame](https://github.com/user-attachments/assets/66745684-8fab-49b4-8a91-c1b37ba86719)

## Build Instructions

### Prerequisites

- C++17 or later
- CMake (minimum version 3.20)

### Build Steps

1. Clone the repository and switch to the rewrite branch:

   ```sh
   git clone -b rewrite https://github.com/CosecSecCot/Top-Down-Game-engine.git
   cd Top-Down-Game-engine
   ```

2. Create a build directory and run CMake:

   ```sh
   mkdir build && cd build
   cmake ..
   ```

3. Compile the engine:

   For Release Mode:

   ```sh
   cmake --build . -DCMAKE_BUILD_TYPE=Release
   ```

   For Debug Mode:

   ```sh
   cmake --build . -DCMAKE_BUILD_TYPE=Debug
   ```

4. Run the executable:

   Executable file is stored in `bin/{Release|Debug}-x86_64/Sandbox/Sandbox`

   ```sh
   cd <root-directory>
   ./bin/Release-x86_64/Sandbox/Sandbox # For Release Mode
   ./bin/Debug-x86_64/Sandbox/Sandbox # For Debug Mode
   ```

## Roadmap

- [ ] Logging
- [ ] Window Events
- [ ] Input Handling

---
*This README is for the `rewrite` branch of TopDown Game Engine and will be
updated as development progresses.*
