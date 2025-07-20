#include "SpaceInvaders.h"
#include "SpaceShip.h"
#include "Obstacle.h"
#include "Alien.h"

#include <raylib.h>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <fstream>

void SpaceInvaders::Init()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, GAME_TITLE);
    SetTargetFPS(GAME_FPS);
    LoadHighScore();
    spaceship = new SpaceShip();
    createObstacles();
    createAliens();
}

void SpaceInvaders::Run()
{
    while (!WindowShouldClose())
    { // Detect window close button or ESC key
        Update();
        BeginDrawing();
        ClearBackground(BLACK);
        Draw();
        EndDrawing();
    }
}
void SpaceInvaders::Update()
{
    HandleInput();
    if(!gameOver)
    {
        // Update game state
        UpdateAliens(); 
        spaceship->UpdateLasers();
        CheckCollisions();        
    }
}
void SpaceInvaders::Draw()
{
    spaceship->Draw();
    for (auto &obstacle : obstacles)
    {
        obstacle.Draw();
    }
    for (auto &alien : aliens)
    {
        alien.Draw();
    }
    DrawUI();
}
void SpaceInvaders::Quit()
{
    SaveHighScore();
    delete spaceship;
    CloseWindow();
}

void SpaceInvaders::HandleInput()
{
    if (IsKeyDown(KEY_LEFT))
    {
        spaceship->Move(-1.0f, 0.0f); // Move left
    }
    if (IsKeyDown(KEY_RIGHT))
    {
        spaceship->Move(1.0f, 0.0f); // Move right
    }
    if (IsKeyPressed(KEY_SPACE))
    {
        spaceship->Shoot();
    }
    if (IsKeyPressed(KEY_ENTER))
    {
        ResetGame();

    }
}

void SpaceInvaders::createObstacles()
{
    // Create 4 obstacles with equal spacing based on the grid size and Screen Width
    int obstacleWidth = Obstacle::grid[0].size() * BLOCK_SIZE;
    int spacing = (WINDOW_WIDTH - (4 * obstacleWidth)) / 5; // Calculate spacing between obstacles
    for (int i = 0; i < 4; ++i)
    {
        Vector2 position = {static_cast<float>(spacing + i * (obstacleWidth + spacing)), static_cast<float>(WINDOW_HEIGHT - 100)};
        obstacles.emplace_back(position, YELLOW); // Create a new obstacle at the calculated position
    }
}

void SpaceInvaders::createAliens()
{
    int alienSpacing = 16; // Spacing between aliens (edge-to-edge)
    int rows = 5;
    int cols = 10;
    int ALIEN_WIDTH = 32;

    int totalGridWidth = (ALIEN_WIDTH * cols) + (alienSpacing * (cols - 1));
    float startX = (WINDOW_WIDTH - totalGridWidth) / 2.0f; // Center horizontally
    float startY = UI_OFFSET_Y + 50.0f; // Start below the top UI boundary

    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            float x = startX + col * (ALIEN_WIDTH + alienSpacing);
            float y = startY + row * (ALIEN_WIDTH + alienSpacing);
            Vector2 position = {x, y};
            int type = 0;
            // Assign alien type based on row
            // Type 2 for the first row, Type 1 for the second and third rows
            // Type 0 for the rest
            if (row == 0)
            {
                type = 2;
            }
            else if (row == 1 || row == 2)
            {
                type = 1;
            }
            else
            {
                type = 0;
            }
            aliens.emplace_back(position, type);
        }
    }
}

void SpaceInvaders::UpdateAliens()
{
    // First pass: Check if any alien has reached the edge and needs direction change
    bool shouldChangeDirection = false;
    for (auto &alien : aliens)
    {
        Vector2 nextPos = alien.getPosition();
        nextPos.x += alienDirection * 2.0f; // Predict next position
        
        if (nextPos.x <= 0 || nextPos.x >= GetScreenWidth() - alien.getTextureWidth())
        {
            shouldChangeDirection = true;
            break;
        }
    }
    
    // Change direction if needed (before updating any aliens)
    if (shouldChangeDirection)
    {
        alienDirection *= -1;
    }
    
    // Second pass: Update all aliens with the correct direction
    for (auto &alien : aliens)
    {
        alien.Update(alienDirection);
    }
}

void SpaceInvaders::CheckCollisions()
{
    // Check for collisions between spaceship lasers and aliens or obstacles
    for (auto &laser : spaceship->lasers)
    {
        if (!laser->active)
            continue; // Skip inactive lasers
        for (auto it = aliens.begin(); it != aliens.end();)
        {
            if (CheckCollisionRecs(laser->GetBounds(), it->GetBounds()))
            {
                // Add score based on alien type
                int points = 0;
                switch (it->getType()) {
                    case 0: points = 10; break;  // Bottom aliens worth 10 points
                    case 1: points = 20; break;  // Middle aliens worth 20 points
                    case 2: points = 30; break;  // Top aliens worth 30 points
                    default: points = 10; break;
                }
                score += points;
                UpdateHighScore(); // Check for new high score
                
                it = aliens.erase(it); // Remove the alien if hit
                laser->active = false; // Deactivate the laser
                std::cout << "Alien hit by laser! +" << points << " points" << std::endl;
                
                // Check if all aliens are destroyed
                if (aliens.empty()) {
                    score += 1000; // Bonus for clearing all aliens
                    UpdateHighScore(); // Check for new high score
                    std::cout << "All aliens destroyed! Bonus: +1000 points" << std::endl;
                    createAliens(); // Create new wave of aliens
                }
            }
            else
            {
                ++it; // Move to the next alien
            }
        }
        // Check for collisions with obstacles
        for (auto &obstacle : obstacles)
        {
            // Check for collision between laser and blocks in the obstacle, remove block if hit
            for (auto it = obstacle.blocks.begin(); it != obstacle.blocks.end();)
            {
                if (CheckCollisionRecs(laser->GetBounds(), it->GetBounds()))
                {
                    it = obstacle.blocks.erase(it); // Remove the block if hit
                    laser->active = false;          // Deactivate the laser
                    std::cout << "Block hit by laser!" << std::endl;
                }
                else
                {
                    ++it; // Move to the next block
                }
            }
        }
    }

    // Check for collisions between alien lasers and the spaceship or obstacles
    for (auto &alien : aliens)
    {
        for (auto it = alien.lasers.begin(); it != alien.lasers.end();)
        {
            if (!(*it)->active)
                continue;
            // Check for collision with the spaceship
            if (CheckCollisionRecs((*it)->GetBounds(), spaceship->GetBounds()))
            {
                std::cout << "Spaceship hit by alien laser!" << std::endl;
                (*it)->active = false; // Deactivate the laser
                lives--;               // Decrease spaceship lives
                if (lives <= 0)
                {
                    GameOver();
                    return;
                }
            }
            else
            {
                // Check for collision with obstacles
                for (auto &obstacle : obstacles)
                {
                    for (auto blockIt = obstacle.blocks.begin(); blockIt != obstacle.blocks.end();)
                    {
                        if (CheckCollisionRecs((*it)->GetBounds(), blockIt->GetBounds()))
                        {
                            blockIt = obstacle.blocks.erase(blockIt); // Remove the block if hit
                            (*it)->active = false;                    // Deactivate the laser
                            std::cout << "Block hit by alien laser!" << std::endl;
                        }
                        else
                        {
                            ++blockIt; // Move to the next block
                        }
                    }
                }
            }
            ++it; // Move to the next alien laser
        }
    }
    
    // Check for direct collisions between aliens and the spaceship
    for (auto &alien : aliens)
    {
        if (CheckCollisionRecs(alien.GetBounds(), spaceship->GetBounds()))
        {
            std::cout << "Alien collided with spaceship! Game Over!" << std::endl;
            GameOver();
            return;
        }
    }
}

void SpaceInvaders::GameOver()
{
    // Handle game over logic
    UpdateHighScore(); // Check and update high score
    std::cout << "Game Over! Your score: " << score << std::endl;
    gameOver = true; // Set game over flag
}

void SpaceInvaders::ResetGame()
{
    lives = 3;
    score = 0;
    spaceship->Reset();
    obstacles.clear();
    aliens.clear();
    createObstacles();
    createAliens();
    alienDirection = 1; // Reset alien direction
    std::cout << "Game has been reset." << std::endl;
    gameOver = false; // Reset game over flag
}

void SpaceInvaders::DrawUI()
{
    // Draw the UI elements like score, lives, etc.
    DrawText(TextFormat("Lives: %d", lives), 50, UI_OFFSET_Y, 20, WHITE);
    DrawText(TextFormat("Score: %d", score), GetScreenWidth() / 2 - 50, UI_OFFSET_Y, 20, WHITE);
    DrawText(TextFormat("High Score: %d", highScore), GetScreenWidth() - 200, UI_OFFSET_Y, 20, WHITE);
    if (gameOver)
    {
        // Draw semi-transparent background for game over text
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.4f)); // Semi-transparent background
        DrawText("Game Over! Press Enter to Restart", GetScreenWidth() / 2 - 150, GetScreenHeight() / 2, 20, RED);
        DrawText(TextFormat("Final Score: %d", score), GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 + 30, 20, WHITE);
    }
}

void SpaceInvaders::UpdateHighScore()
{
    if (score > highScore) {
        highScore = score;
        SaveHighScore();
        std::cout << "New High Score: " << highScore << std::endl;
    }
}

void SpaceInvaders::SaveHighScore()
{
    std::ofstream file("highscore.txt");
    if (file.is_open()) {
        file << highScore;
        file.close();
    }
}

void SpaceInvaders::LoadHighScore()
{
    std::ifstream file("highscore.txt");
    if (file.is_open()) {
        file >> highScore;
        file.close();
    } else {
        highScore = 0; // Default high score if file doesn't exist
    }
}
