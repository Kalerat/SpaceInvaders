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

The game can now be run directly from where the executable is built, as resources are automatically copied to the correct location during the build process.

#### On Windows:
```bash
# Navigate to where the executable is located
cd build\Debug
.\SpaceInvaders.exe

# OR if Release build:
cd build\Release
.\SpaceInvaders.exe
```

#### On Linux/macOS:
```bash
# Navigate to the build directory
cd build
./SpaceInvaders
```

**Note**: The build process automatically copies the `resources/` folder to the same directory as the executable, so you need to run the game from that directory.

## Game Assets

The following image files are required and will be automatically copied to the executable directory during build:
- `spaceship.png` - Player spaceship sprite
- `alien_0.png` - Bottom row alien sprite (10 points)
- `alien_1.png` - Middle row alien sprite (20 points)  
- `alien_2.png` - Top row alien sprite (30 points)

These files must be present in the `resources/` directory at the project root. The build system automatically copies them to the correct location next to the executable.

## Project Structure

```
SpaceInvaders/
├── CMakeLists.txt          # Build configuration
├── README.md               # This file
├── build/                  # Build output directory
│   ├── Debug/              # Debug build (Windows)
│   │   ├── SpaceInvaders.exe
│   │   └── resources/      # Resources copied here automatically
│   ├── Release/            # Release build (Windows)
│   │   ├── SpaceInvaders.exe
│   │   └── resources/      # Resources copied here automatically
│   ├── SpaceInvaders       # Executable (Linux/macOS)
│   └── resources/          # Resources copied here automatically
├── resources/              # Game assets (IMPORTANT: needed for runtime)
│   ├── spaceship.png
│   ├── alien_0.png
│   ├── alien_1.png
│   └── alien_2.png
└── src/                    # Source code
    ├── main.cpp           # Entry point
    ├── SpaceInvaders.h    # Main game class header
    ├── SpaceInvaders.cpp  # Main game logic
    ├── SpaceShip.h        # Player spaceship header
    ├── SpaceShip.cpp      # Player spaceship implementation
    ├── Alien.h            # Alien class header
    ├── Alien.cpp          # Alien implementation
    ├── Obstacle.h         # Destructible obstacles header
    ├── Obstacle.cpp       # Obstacle implementation
    ├── Block.h            # Individual block component header
    ├── Block.cpp          # Block implementation
    ├── Laser.h            # Laser projectile header
    └── Laser.cpp          # Laser implementation
```

## Technical Details

- **Graphics Library**: Raylib
- **Language**: C++17
- **Build System**: CMake
- **Dependencies**: Raylib (automatically downloaded via CMake)
- **Window Size**: 800x800 pixels
- **Target FPS**: 60 FPS
- **Resource Management**: Resources automatically copied to executable directory during build

## Troubleshooting

### Build Issues
- Ensure CMake is properly installed and in your PATH
- Make sure you have a C++17 compatible compiler
- On Windows, the executable will be in `build/Debug/` or `build/Release/`
- On Linux/macOS, the executable will be directly in the `build/` directory

### Runtime Issues
- **"Failed to load texture" errors**: 
  - Ensure you've built the project (which copies resources automatically)
  - Verify that resource files (PNG images) are present in the `resources/` directory at project root
  - If resources aren't copied, try rebuilding the project
- **Game crashes immediately**: Usually indicates missing resource files
- **High score not saving**: Ensure the executable has write permissions in its directory

### Recommended Setup
**Run the game from the executable's directory:**
```bash
# Windows:
cd build\Debug
.\SpaceInvaders.exe

# Or for Release build:
cd build\Release  
.\SpaceInvaders.exe

# Linux/macOS:
cd build
./SpaceInvaders
```

**Alternative - You can also double-click the executable directly in File Explorer/Finder, as the resources are now in the same directory!**

This project is for educational purposes. Raylib is licensed under the zlib/libpng license.