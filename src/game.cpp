#include "game.hpp"
#include <iostream>

void Game::CheckForCollision()
{
    for (auto &laser : spaceship.lasers)
    {
        auto it = aliens.begin();
        while (it != aliens.end())
        {
            if (CheckCollisionRecs(it->getRect(), laser.getRect()))
            {
                PlaySound(explosionSound);
                it = aliens.erase(it);
                if (it->GetType() == 1)
                {
                    score += 100;
                }
                if (it->GetType() == 2)
                {
                    score += 200;
                }
                else
                {
                    score += 300;
                }
                laser.active = false;
            }
            else
            {
                ++it;
            }
            for (auto &obstacle : obstacles)
            {
                auto it = obstacle.blocks.begin();
                while (it != obstacle.blocks.end())
                {
                    if (CheckCollisionRecs(it->getRect(), laser.getRect()))
                    {
                        it = obstacle.blocks.erase(it);
                        laser.active = false;
                    }
                    else
                    {
                        ++it;
                    }
                }
            }
            if (CheckCollisionRecs(mysteryShip.getRect(), laser.getRect()))
            {
                mysteryShip.alive = false;
                laser.active = false;
                score += 500;
            }
        }
    }

    for (auto &alienLaser : alienLasers)
    {
        if (CheckCollisionRecs(spaceship.getRect(), alienLaser.getRect()))
        {
            alienLaser.active = false;
            lives--;
            std::cout << "OUCH! The alien hit you! " + std::to_string(lives) + " lives remaining!" << std::endl;
            GameOver();
            continue;
        }
        for (auto &obstacle : obstacles)
        {
            auto itBlock = obstacle.blocks.begin();
            while (itBlock != obstacle.blocks.end())
            {
                if (CheckCollisionRecs(itBlock->getRect(), alienLaser.getRect()))
                {
                    itBlock = obstacle.blocks.erase(itBlock); // Rimuove il blocco
                    alienLaser.active = false;
                    break; // Esce dal while dopo la prima collisione
                }
                else
                {
                    ++itBlock;
                }
            }
        }
    }

    for (auto &alien : aliens)
    {
        for (auto &obstacle : obstacles)
        {
            auto itBlock = obstacle.blocks.begin();
            while (itBlock != obstacle.blocks.end())
            {
                if (CheckCollisionRecs(itBlock->getRect(), alien.getRect()))
                {
                    itBlock = obstacle.blocks.erase(itBlock); // Rimuove il blocco
                    break;                                    // Esce dal while dopo la prima collisione
                }
                else
                {
                    ++itBlock;
                }
            }
        }
        if (CheckCollisionRecs(spaceship.getRect(), alien.getRect()))
        {
            lives = 0;
            GameOver();
        }
    }
    if (aliens.size() == 0)
    {
        NextLevel();
    }
}

int Game::Reset()
{
    spaceship.Reset();
    aliens.clear();
    alienLasers.clear();
    obstacles.clear();
    return 0;
}

int Game::GameOver()
{
    if (lives == 0)
    {
        std::cout << "Game Over!" << std::endl;
        std::cout << "Press ENTER to restart!" << std::endl;
        run = false;
    }
    return 0;
}

int Game::InitGame()
{
    obstacles = GenerateObstacles();
    aliens = GenerateAliens();
    aliensDirection = 1;
    timeLastAlienFired = 0.0;
    mysteryShipSpawnInterval = GetRandomValue(10, 20);
    lives = 3;
    score = 0;
    run = true;
    level = 1;
    return 0;
}

void Game::NextLevel()
{
    ++level;
    alienLaserShootInterval -= 0.10;
    spaceship.Reset();
    aliens.clear();
    alienLasers.clear();
    aliens = GenerateAliens();
}

Game::Game()
{
    music = LoadMusicStream("resources/sounds/Sounds_music.ogg");
    explosionSound = LoadSound("resources/sounds/Sounds_explosion.ogg");
    alienLaserShootInterval = 0.50;
    PlayMusicStream(music);
    InitGame();
}

Game::~Game()
{
    Alien::UnloadImages();
    UnloadMusicStream(music);
    UnloadSound(explosionSound);
}

void Game::Draw()
{
    spaceship.Draw();
    for (auto &laser : spaceship.lasers)
    {
        laser.Draw();
    }
    for (auto &obstacle : obstacles)
    {
        obstacle.Draw();
    }
    for (auto &alien : aliens)
    {
        alien.Draw();
    }
    for (auto &alienLaser : alienLasers)
    {
        alienLaser.Draw();
    }
    mysteryShip.Draw();
}

void Game::Update()
{
    if (run)
    {

        for (auto &laser : spaceship.lasers)
        {
            laser.Update();
        }
        MoveAliens();
        AlienShootLaser();
        for (auto &laser : alienLasers)
        {
            laser.Update();
        }

        double currentTime = GetTime();
        if (currentTime - timeLastSpawn > mysteryShipSpawnInterval)
        {
            mysteryShip.Spawn();
            timeLastSpawn = GetTime();
            mysteryShipSpawnInterval = GetRandomValue(10, 20);
        }

        DeleteInactiveLasers();
        mysteryShip.Update();

        CheckForCollision();
    }
}

void Game::HandleInput()
{
    if (run)
    {
        if (IsKeyDown(KEY_RIGHT))
        {
            spaceship.MoveRight();
        }
        if (IsKeyDown(KEY_LEFT))
        {
            spaceship.MoveLeft();
        }
        if (IsKeyPressed(KEY_SPACE))
        {
            spaceship.FireLaser();
        }
    }
    else
    {
        if (IsKeyDown(KEY_ENTER))
        {
            Reset();
            InitGame();
        }
    }
}

bool Game::GetRun()
{
    return run;
}

int Game::GetLives()
{
    return lives;
}

int Game::GetScore()
{
    return score;
}

int Game::GetLevel()
{
    return level;
}

Music Game::getMusic()
{
    return music;
}

void Game::DeleteInactiveLasers()
{
    for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();)
    {
        if (it->IsOutOfScreen())
        {
            it = spaceship.lasers.erase(it);
        }
        else if (!it->active)
        {
            it = spaceship.lasers.erase(it);
        }
        else
        {
            ++it;
        }
    }
    for (auto it = alienLasers.begin(); it != alienLasers.end();)
    {
        if (it->IsOutOfScreen())
        {
            it = alienLasers.erase(it);
        }
        else if (!it->active)
        {
            it = alienLasers.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

std::vector<Obstacle> Game::GenerateObstacles()
{
    int obstacleWidth = Obstacle::grid[0].size() * 3;
    float gap = (float)(GetScreenWidth() - (4 * obstacleWidth)) / 5; // LARGHEZZA TOTALE - LARGHEZZA TOTALE DEGLI OSTACOLI DIVISO IL NUMERO DEI GAP DA CREARE

    for (int i = 0; i < 4; i++)
    {
        float offsetX = (i + 1) * gap + i * obstacleWidth;
        obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() - 200)}));
    }

    return obstacles;
}

std::vector<Alien> Game::GenerateAliens()
{
    float cell_size = 55; // PIXEL
    float center_x = 75;
    float center_y = 110;
    std::vector<Alien> aliens;
    for (int row = 0; row < 5; row++)
    {
        for (int column = 0; column < 11; column++)
        {
            int alienType;
            if (row == 0)
            {
                alienType = 3;
            }
            else if (row == 1 || row == 2)
            {
                alienType = 2;
            }
            else
            {
                alienType = 1;
            }
            float x = center_x + column * cell_size;
            float y = center_y + row * cell_size;
            aliens.push_back(Alien(alienType, {x, y}));
        }
    }
    return aliens;
}

void Game::MoveAliens()
{
    for (auto &alien : aliens)
    {
        if (alien.position.x + alien.alienImages[alien.GetType() - 1].width > GetScreenWidth() - 25)
        {
            aliensDirection = -1;
            MoveDownAliens(4);
        }
        if (alien.position.x < 25)
        {
            aliensDirection = 1;
            MoveDownAliens(4);
        }
        alien.Update(aliensDirection);
    }
}

void Game::MoveDownAliens(int y)
{
    for (auto &alien : aliens)
    {
        alien.position.y += y;
    }
}

void Game::AlienShootLaser()
{
    double currentTime = GetTime();
    if (currentTime - timeLastAlienFired >= alienLaserShootInterval && !aliens.empty())
    {
        int randomIndex = GetRandomValue(0, aliens.size() - 1);
        Alien &alien = aliens[randomIndex];
        alienLasers.push_back(Laser({alien.position.x + alien.alienImages[alien.GetType() - 1].width / 2, alien.position.y + alien.alienImages[alien.GetType() - 1].height}, -6));
        timeLastAlienFired = GetTime();
    }
}
