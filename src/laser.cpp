#include "laser.hpp"

Laser::Laser(Vector2 position, float speed)
{
    // image = LoadTexture("resources/laser.png");
    this->position = position;
    this->speed = speed;
    this->active = true;
}

Laser::~Laser()
{
    // UnloadTexture(image);
}

void Laser::Draw()
{
    if (IsOutOfScreen())
    {
        active = false;
        return;
    }
    if (!active)
        return;
    DrawRectangle(position.x, position.y, 10, 20, {243, 216, 63, 255});
}

void Laser::Update()
{
    if (!active)
        return;
    position.y -= speed;
}

bool Laser::IsOutOfScreen()
{
    return position.y < 0 || position.y > GetScreenHeight();
}

Rectangle Laser::getRect()
{
    return {position.x, position.y, 10, 20};
}
