# Cosec Engine *(Rewrite Branch)*

## Overview

This branch contains the complete rewrite of **Cosec Engine**, inspired by
[The Cherno's Game Engine series](https://youtube.com/playlist?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT&si=kWuiV_w8-P1DgTe-).
The goal of this rewrite is to build a high-performance, modular, and scalable
game engine from the ground up, following best practices.

<!--
![screenshot-20241109-154218Z-selected](https://github.com/user-attachments/assets/6ee2e0c7-7378-44ad-a144-b2c6917a227d)
-->

<!---
![screenshot-20241120-122706Z-selected](https://github.com/user-attachments/assets/59d7dfb0-8966-49e3-8e78-f8a1c497851d)
-->

![CosecEngine](https://github.com/user-attachments/assets/66745684-8fab-49b4-8a91-c1b37ba86719)

## Build Instructions

### Prerequisites

- C++17 or later
- CMake (minimum version 3.20)
- [spdlog](https://github.com/gabime/spdlog) (included as a submodule)
- [GLFW](https://github.com/glfw/glfw) (included as a submodule)
- [Glad](http://glad.dav1d.de/) (included in the repository)
- [ImGui](https://github.com/ocornut/imgui/tree/docking) (included as a submodule)
- [GLM](https://github.com/g-truc/glm/) (included as a submodule)

### Build Steps

1. Clone the repository and switch to the rewrite branch:

   ```sh
   git clone -b rewrite https://github.com/CosecSecCot/Cosec-Engine.git
   cd Cosec-Engine
   ```

2. Create a build directory and configure CMake:

   ```sh
   mkdir build && cd build
   cmake ..
   ```

   By Default `CosecEngine` builds as a **Static** library.

   If you want to build `CosecEngine` as a **Shared** library use:

   ```sh
   mkdir build && cd build
   cmake .. -DCOSEC_SHARED=ON  # Build as a Shared library instead
   ```

   #### Building on Linux

   By default, **X11** is selected.

   If you want to enable **Wayland** instead use:

   ```sh
   cmake .. -DUSE_WAYLAND=ON
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

   Executable file is stored in

   `bin/Release-x86_64/Sandbox/` for Release Mode:

   ```sh
   cd <root-directory>
   ./bin/Release-x86_64/Sandbox/Sandbox
   ```

   `bin/Debug-x86_64/Sandbox/` for Debug Mode:

   ```sh
   cd <root-directory>
   ./bin/Debug-x86_64/Sandbox/Sandbox
   ```

## Roadmap

- [x] Logging
- [x] Setup Window with GLFW
- [x] Window Events
- [x] Input Handling
- [x] ImGui Setup
- [ ] `Renderer` draws a triangle
- [ ] Abstraction of `Renderer` API

---
*This README is for the `rewrite` branch of Cosec Engine and will be
updated as development progresses.*
