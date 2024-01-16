# Primal Engine

## Introduction

Primal Engine is a videogame engine for 3rd grade subject 'Game Engines' of the videogame design and development grade at [CITM](https://www.citm.upc.edu/) - [UPC](https://www.upc.edu/ca).

## Team

**Iván Bermúdez Sagra**

![Ivan](https://github.com/Maksym203/PrimalEngine/assets/99950357/06fab285-dccd-4691-a114-78c96f71b093)

* Documentation
* Camera controls
* Menus
* Play/Pause/Stop
* Animation
* Website

**Maksym Polupan**

![Maksym](https://github.com/Maksym203/PrimalEngine/assets/99950357/e4c2f7b0-2f04-41c3-9da0-a85f7c149c2b)

* Libraries implementation
* Docking
* Buffers
* FBX Loading
* Textures
* Animation
* Bones

## Main-core subsystems

* Model creation, delete, import + Drag & Drop
* Inspector (Game object hierarchy, transform with guizmos, mesh, texture, camera)
* Unity-like camera controls
* Editor tools
* Game viewport
* Serialization (Configuration & Scene json files)
* Play/Pause/Stop
* Camera (Component, mouse picking & frustum culling)

## Skeletal Animation

The engine has the animation channels practically done, unfortunately the implementation of the bones is not finished, so the animations cannot work yet.

## Video

## Controls

### Basic camera movement
* **Hold Left Shift:** Movement speed up.
* **Left/Right Arrow:** Move left/right.
* **Up/Down Arrow:** Zoom in/out.
* **F:** Focus camera around the geometry.

### Flythrough mode
**While Right Clicking:**
* Free look around.
* **A/D:** Move left/right.
* **W/S:** Zoom in/out.
* **Q/E:** Move up/down.

### Orbit camera
* Left Alt + Left Clicking

### Mouse wheel functions
* Pan movement (Free move in x & y) while clicking the mouse wheel button.
* Zoom in/out with the mouse wheel

## Repository

Check out:

* [Github repository](https://github.com/Maksym203/PrimalEngine)
* [Last release](https://github.com/IvanBSupc/Primal_Engine/releases/tag/v0.2)

## License

MIT License

Copyright (c) 2023 Ivan Bermudez Sagra & Maksym Polupan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
