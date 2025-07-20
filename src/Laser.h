#pragma once

#include <raylib.h>


class Laser {
public:
    Laser(Vector2 position, float speed);
    ~Laser();
    
    void Update();
    void Draw();
    Rectangle GetBounds() const { return { position.x, position.y, 5.0f, 20.0f }; }
    
    bool active;
private:
    Vector2 position;
    float speed;
};
