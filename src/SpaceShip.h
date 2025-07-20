#pragma once

#include "Laser.h"

#include <raylib.h>
#include <vector>
#include <memory>

class SpaceShip {
public:
    SpaceShip();
    ~SpaceShip();
    
    std::vector<std::unique_ptr<Laser>> lasers; // List of lasers shot by the spaceship

    void Draw();
    void Move(float deltaX, float deltaY);
    void Shoot();
    void Reset();
    void UpdateLasers();
    Rectangle GetBounds() const { return { position.x, position.y, static_cast<float>(texture.width), static_cast<float>(texture.height) }; }

    private:
    Texture2D texture; // Texture for the spaceship
    Vector2 position; // Position of the spaceship
    float speed; // Speed of the spaceship
};
