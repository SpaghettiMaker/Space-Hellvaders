#pragma once
#include <raylib.h>

class Alien
{
private:
    int type;

public:
    Alien(int type, Vector2 position);
    void Update(int direction);
    void Draw();
    Vector2 position;
    int GetType();
    static Texture2D alienImages[3];
    static void UnloadImages();
    Rectangle getRect();
};