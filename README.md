# FAST Shooter 🚀

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++](https://img.shields.io/badge/C++-17-blue.svg)](https://isocpp.org/)

**FAST Shooter** is a fast-paced 2D space shooter built entirely in C++. Dodge enemies, manage your fire, and survive as long as possible. 

## 🎮 Gameplay / Screenshots

> **Note to Developer:** Put a high-quality, 60fps GIF of your gameplay right here. If people can't see the game moving, they won't bother building it. Below that, add 1-2 static screenshots.

![Gameplay Demo](link_to_your_gif_here.gif)

## ✨ Features

* **Three Difficulty Tiers:**
    * 🟢 **Easy:** Slower enemy spawns, forgiving mechanics.
    * 🟡 **Medium:** Standard pacing, balanced challenge.
    * 🔴 **Hard:** Relentless enemy waves and faster projectiles.
* **Hardware Accelerated:** Fully utilizes GPU rendering for smooth, tear-free framerates.
* **Clean Architecture:** Written in modern C++ with a focus on performance and memory management.

## ⌨️ Controls

| Action | Keybinding |
| :--- | :--- |
| **Move Up** | `W` or `Up Arrow` |
| **Move Down** | `S` or `Down Arrow` |
| **Move Left** | `A` or `Left Arrow` |
| **Move Right** | `D` or `Right Arrow` |
| **Shoot** | `Spacebar` |
| **Pause Game** | `ESC` |

## 🛠️ Dependencies

To build and run this game, you will need the following installed on your system:

* **C++ Compiler:** GCC or Clang (Must support C++17 or higher)
* **Build System:** CMake (v3.10+)
* **Graphics Library:** SFML 2.5+ *(Update this if you used SDL2, Raylib, etc.)*

## 🚀 Building from Source

### Linux (Arch/Rolling Release)

1. Install the required dependencies and build tools:
   ```bash
   sudo pacman -S base-devel cmake sfml
