#pragma once
#include <raylib.h>

class Laser
{
public:
    Laser(Vector2 position, float speed);
    ~Laser();
    void Draw();
    void Update();
    bool IsOutOfScreen();
    Rectangle getRect();
    bool active;

private:
    Texture2D image;
    Vector2 position;
    float speed;
};