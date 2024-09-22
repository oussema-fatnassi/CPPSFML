# CPPSFML
## Brick breaker

This project is a modern take on the classic brick breaker game, implemented in C++ using the SFML (Simple and Fast Multimedia Library) framework.
 The game features a unique twist where player control a cannon to shoot balls at bricks, instead of the traditional paddle gameplay.


## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
- [How to Play](#how-to-play)
- [Libraries Used](#libraries-used)
- [Credits](#contributing)


## Overview

This project is divided into two main parts:

- Creation of a simple game engine using SFML
- Implementation of a brick breaker game using the custom game engine

The game engine provides core functionality for game objects, collision detection, and input management. The brick breaker game utilizes this engine to create an engaging gameplay experience.


## Features
Game Engine

- GameObject management (circles and rectangles)
- Movement and rotation of game objects
- Collision detection using AABB (Axis-Aligned Bounding Box)
- Input management for keyboard and mouse events
- Cannon controlled by mouse movement
- Ball shooting mechanics
- Brick grid generation
- Collision handling for balls, bricks, and screen boundaries
- Brick health system (multiple hits required to destroy)

## Installation

### Prerequisites
- C++ compiler (GCC, Clang, or MSVC recommended).
- CMake for building the project.
- SFML libraries installed on your system.

### Building the Project

1. **Clone the repository:**
   ```bash
   git clone https://github.com/oussema-fatnassi/CPPSFML.git


## How to Play:
  - Run the executable generated in the build directory.
  - Use the mouse to aim the cannon.
  - Left-click to shoot a ball.
  - Destroy all the bricks to win the game.


## Libraries Used
 - SFML: A simple and fast multimedia library that provides easy-to-use classes for graphics, windowing, and handling inputs.


   
## Credits
- Developed by Oussema Fatnassi, Baptiste Appriou, Ali Abakar Issa
