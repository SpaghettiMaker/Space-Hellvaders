#pragma once
#include <raylib.h>

class Block
{
public:
    Block();
    Block(Vector2 position);
    ~Block();
    void Draw();

private:
    Vector2 position;
    Color color;
    float size;
};