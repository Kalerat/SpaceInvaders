#pragma once

#include "SpaceShip.h"
#include "Obstacle.h"
#include "Alien.h"

#include <raylib.h>
#include <stdexcept>

// Global constants
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define UI_OFFSET_X 50
#define UI_OFFSET_Y 50
#define GAME_TITLE "Space Invaders with raylib"
#define GAME_FPS 60


class SpaceInvaders {
public:
    SpaceInvaders();

    int lives = 3; // Number of lives for the spaceship
    int score = 0; // Player's score
    int highScore = 0; // High score
    bool gameOver = false; // Flag to indicate if the game is over


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
    void CheckCollisions();
    void GameOver();
    void ResetGame();
    void DrawUI();
    void UpdateHighScore();
    void SaveHighScore();
    void LoadHighScore();
};