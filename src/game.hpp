#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"
#include "alien.hpp"
#include "mysteryship.hpp"
class Game
{
private:
    Spaceship spaceship;
    std::vector<Obstacle> obstacles;
    void DeleteInactiveLasers();
    std::vector<Obstacle> GenerateObstacles();
    std::vector<Alien> aliens;
    std::vector<Alien> GenerateAliens();
    void MoveAliens();
    void MoveDownAliens(int y);
    int aliensDirection;
    std::vector<Laser> alienLasers;
    void AlienShootLaser();
    constexpr static float alienLaserShootInterval = 0.35;
    float timeLastAlienFired;
    MysteryShip mysteryShip;
    float mysteryShipSpawnInterval;
    float timeLastSpawn;
    void CheckForCollision();
    int lives;
    bool run;
    int Reset();
    int GameOver();
    int InitGame();
    int score;
    Sound explosionSound;
    Music music;

public:
    Game();
    ~Game();
    void Draw();
    void Update();
    void HandleInput();
    bool GetRun();
    int GetLives();
    int GetScore();
    Music getMusic();
};
