#pragma once

#include <raylib.h>


#define BLOCK_SIZE 3 // Each block is 3x3 pixels

class Block {
public:
    Block(Vector2 position, Color color = YELLOW);
    ~Block();

    Rectangle GetBounds() const { return { position.x, position.y, static_cast<float>(BLOCK_SIZE), static_cast<float>(BLOCK_SIZE) }; }

    void Draw();

private:
    Vector2 position;
    Color color;
};
