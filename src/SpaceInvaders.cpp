#include "SpaceInvaders.h"
#include "SpaceShip.h"
#include "Obstacle.h"
#include "Alien.h"

#include <raylib.h>
#include <stdexcept>
#include <iostream>


SpaceInvaders::SpaceInvaders() {
    // Constructor implementation
}
SpaceInvaders::~SpaceInvaders() {
    // Destructor implementation
}
void SpaceInvaders::Init() {
    // Initialization code for Space Invaders
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, GAME_TITLE);
    SetTargetFPS(GAME_FPS);
    spaceship = new SpaceShip(); // Create a new spaceship instance
    createObstacles();
    createAliens();
}

void SpaceInvaders::Run() {
    while (!WindowShouldClose()) { // Detect window close button or ESC key
        Update();
        BeginDrawing();
        ClearBackground(BLACK);
        Draw();
        EndDrawing();
    }
}
void SpaceInvaders::Update() {
    // Update game state for Space Invaders
    HandleInput();
    UpdateAliens(); // Update the aliens' positions
    spaceship->UpdateLasers(); // Update the lasers shot by the spaceship
}
void SpaceInvaders::Draw() {
    spaceship->Draw(); // Draw the spaceship
    for (auto& obstacle : obstacles) {
        obstacle.Draw(); // Draw each obstacle
    }
    for (auto& alien : aliens) {
        alien.Draw(); // Draw each alien
    }
}
void SpaceInvaders::Quit() {
    // Cleanup code for Space Invaders
}

// Handle user input
void SpaceInvaders::HandleInput() {
    if (IsKeyDown(KEY_LEFT)) {
        spaceship->Move(-1.0f, 0.0f); // Move left
    }
    if (IsKeyDown(KEY_RIGHT)) {
        spaceship->Move(1.0f, 0.0f); // Move right
    }
    if (IsKeyPressed(KEY_SPACE)) {
        spaceship->Shoot();
    }
}

void SpaceInvaders::createObstacles() {

    // Create 4 obstacles with equal spacing based on the grid size and Screen Width
    int obstacleWidth = Obstacle::grid[0].size() * BLOCK_SIZE;
    int spacing = (WINDOW_WIDTH - (4 * obstacleWidth)) / 5; // Calculate spacing between obstacles
    for (int i = 0; i < 4; ++i) {
        Vector2 position = {static_cast<float>(spacing + i * (obstacleWidth + spacing)), static_cast<float>(WINDOW_HEIGHT - 100)};
        obstacles.emplace_back(position, YELLOW); // Create a new obstacle at the calculated position
    }

}

void SpaceInvaders::createAliens() {
    int alienSpacing = 16; // Spacing between aliens (edge-to-edge)
    int rows = 5;
    int cols = 10;
    int ALIEN_WIDTH = 32;

    int totalGridWidth = (ALIEN_WIDTH * cols) + (alienSpacing * (cols - 1));
    float startX = (WINDOW_WIDTH - totalGridWidth) / 2.0f;
    float startY = 50.0f;

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            float x = startX + col * (ALIEN_WIDTH + alienSpacing);
            float y = startY + row * (ALIEN_WIDTH + alienSpacing);
            Vector2 position = {x, y};
            int type = 0;
            if (row == 0) {
                type = 2;
            } else if (row == 1 || row == 2) {
                type = 1;
            } else {
                type = 0;
            }
            aliens.emplace_back(position, type);
        }
    }
}

void SpaceInvaders::UpdateAliens() {
    for (auto& alien : aliens) {
        alien.Update(alienDirection);
        // Check if the alien has reached the edge of the screen
        if (alien.getPosition().x <= 0 || alien.getPosition().x >= GetScreenWidth() - alien.getTextureWidth()) {
            alienDirection *= -1; // Change direction
            break; // Exit the loop to avoid modifying the vector while iterating
        }
    }
}