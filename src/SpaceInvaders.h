#pragma once

#include "SpaceShip.h"
#include "Obstacle.h"
#include "Alien.h"

#include <raylib.h>
#include <stdexcept>



//------------------------------------------------------------------------------------
// Global Variables Definition
//------------------------------------------------------------------------------------
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define GAME_TITLE "Space Invaders with raylib"
#define GAME_FPS 60


class SpaceInvaders {
public:
    SpaceInvaders();
    ~SpaceInvaders();

    void Init();
    void Run();
    void Quit();
    
    private:
    SpaceShip* spaceship;
    std::vector<Obstacle> obstacles;
    std::vector<Alien> aliens;
    int alienDirection = 1; // 1 for right, -1 for left
    void Update();
    void Draw();
    void HandleInput();
    void createObstacles();
    void createAliens();
    void UpdateAliens();
};