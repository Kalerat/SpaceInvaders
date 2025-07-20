#include "Block.h"

Block::Block(Vector2 position, Color color)
    : position(position), color(color) {
    // Constructor implementation
}
Block::~Block() {
    // Destructor implementation
}

void Block::Draw() {
    DrawRectangle(position.x, position.y, BLOCK_SIZE, BLOCK_SIZE, color);
}

