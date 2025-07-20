#include "Alien.h"
#include "SpaceInvaders.h"
#include <iostream>


bool Alien::loaded = false;
Texture2D Alien::texture[3] = {};

Alien::Alien(Vector2 position, int type) : position(position), type(type) {
    
    std::cout << "Creating alien of type: " << type << std::endl;

    if(!loaded) {
        loadTextures();
    }
}
void Alien::Draw() {
    DrawTexture(texture[type], static_cast<int>(position.x), static_cast<int>(position.y), WHITE);
    for (const auto& laser : lasers) {
        laser->Draw();
    }
}
void Alien::Update(int direction) {
    // Move the alien down when direction changes
    if (lastDirection != direction) {
        lastDirection = direction;
        position.y += 10.0f; // Move the alien down when direction changes
    }
    
    // Move horizontally
    position.x += direction * 2.0f; // Move the alien left or right
    
    // Clamp to screen boundaries
    if (position.x < 0) position.x = 0;
    if (position.x > GetScreenWidth() - texture[type].width) position.x = GetScreenWidth() - texture[type].width;

    // Check if the alien should shoot a laser
    if (GetRandomValue(0, 1000) < 1) { // 0.1% chance to shoot
        shootLaser();
    }
    // Update lasers
    for (auto it = lasers.begin(); it != lasers.end();) {
        (*it)->Update();
        if (!(*it)->active) {
            it = lasers.erase(it); // Remove inactive lasers
        } else {
            ++it; // Move to the next laser
        }
    }
}


void Alien::loadTextures() {
        for (int i = 0; i < 3; ++i) {
            std::string texturePath = "resources/alien_" + std::to_string(i) + ".png";
            texture[i] = LoadTexture(texturePath.c_str());
            if (texture[i].id == 0) {
                std::cout << "Failed to load: " << texturePath << ", falling back to alien_0.png\n";
                texture[i] = LoadTexture("resources/alien_0.png");
            }
        }
        loaded = true;
}


void Alien::shootLaser() {
    Vector2 laserPosition = { position.x + texture[type].width / 2, position.y + texture[type].height };
    this->lasers.push_back(std::make_unique<Laser>(laserPosition, -200.0f));
}