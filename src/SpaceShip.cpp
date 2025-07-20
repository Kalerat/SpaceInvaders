#include "SpaceShip.h"
#include "Laser.h"
#include "SpaceInvaders.h"

#include <raylib.h>
#include <stdexcept>

SpaceShip::SpaceShip() {
    // Load spaceship texture
    texture = LoadTexture("resources/spaceship.png");
    if (texture.id == 0) {
        // Handle texture loading failure
        throw std::runtime_error("Failed to load spaceship texture");
    }
    // Initialize spaceship position and speed
    position = { static_cast<float>(GetScreenWidth() / 2), static_cast<float>(GetScreenHeight() - texture.height - 20) };
    speed = 200.0f; // Set a default speed for the spaceship

}
SpaceShip::~SpaceShip() {
    // Unload spaceship texture
    UnloadTexture(texture);
}
void SpaceShip::Draw() {
    DrawTexture(texture, static_cast<int>(position.x), static_cast<int>(position.y) , WHITE);
    for (const auto& laser : lasers) {
        laser->Draw();
    }
}
void SpaceShip::Move(float deltaX, float deltaY) {
    position.x += deltaX * speed * GetFrameTime();
    position.y += deltaY * speed * GetFrameTime();
    
    // Clamp position to respect UI boundaries (only top has offset)
    if (position.x < 0) position.x = 0;
    if (position.x > GetScreenWidth() - texture.width) position.x = GetScreenWidth() - texture.width;
    if (position.y < UI_OFFSET_Y) position.y = UI_OFFSET_Y;
    if (position.y > GetScreenHeight() - texture.height) position.y = GetScreenHeight() - texture.height;
}
void SpaceShip::Shoot() {
    lasers.push_back(std::make_unique<Laser>(Vector2{ position.x + texture.width / 2, position.y }, 300.0f));
}

void SpaceShip::UpdateLasers() {
    for (auto it = lasers.begin(); it != lasers.end();) {
        (*it)->Update();
        if (!(*it)->active) {
            it = lasers.erase(it); // Remove inactive lasers
        } else {
            ++it; // Move to the next laser
        }
    }
}

void SpaceShip::Reset() {
    position = { static_cast<float>(GetScreenWidth() / 2), static_cast<float>(GetScreenHeight() - texture.height - 20) };
    lasers.clear(); // Clear all lasers
}