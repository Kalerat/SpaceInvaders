# Space Invaders with Raylib

A classic Space Invaders game implementation in C++ using the Raylib graphics library. Features include alien waves, destructible obstacles, scoring system, high score persistence, and UI boundaries for clean gameplay presentation.

## Features

- **Classic Gameplay**: Control a spaceship to defend against waves of descending aliens
- **Multiple Alien Types**: Different alien types with varying point values (10, 20, 30 points)
- **Destructible Obstacles**: Strategic cover that can be destroyed by both player and alien lasers
- **Scoring System**: Points for destroying aliens with bonus points for clearing entire waves
- **High Score Persistence**: High scores are saved to file and persist between game sessions
- **Lives System**: Player has 3 lives, loses one when hit by alien lasers

## Controls

- **Arrow Keys (Left/Right)**: Move spaceship
- **Spacebar**: Shoot laser
- **Enter**: Restart game (when game over)

## Prerequisites

- C++ compiler (GCC, Clang, or MSVC)
- CMake (version 3.10 or higher)
- Git

## Installation & Setup

### 1. Clone the Repository

```bash
git clone https://github.com/Kalerat/SpaceInvaders.git
cd SpaceInvaders
```

### 2. Build the Project

The project uses CMake and automatically downloads Raylib as a dependency.

#### On Windows (PowerShell/Command Prompt):

```bash
# Create build directory
mkdir build
cd build

# Generate build files
cmake ..

# Compile the project
cmake --build .
```

#### On Linux/macOS:

```bash
# Create build directory
mkdir build
cd build

# Generate build files
cmake ..

# Compile the project
make
```

### 3. Run the Game

#### On Windows:
```bash
# From the build directory
.\SpaceInvaders.exe
```

#### On Linux/macOS:
```bash
# From the build directory
./SpaceInvaders
```

This project is for educational purposes. Raylib is licensed under the zlib/libpng license.