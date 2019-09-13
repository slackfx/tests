#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <string>

const uint32_t WINDOW_WIDTH = 640;
const uint32_t WINDOW_HEIGHT = 480;

const uint16_t TILE_SIZE = 32;
const uint16_t INITIAL_MAX_JUMP_HEIGHT = 100;
const int FIELD_WIDTH = 20;
const int FIELD_HEIGHT = 15;

/*
int playerX = 2;
int playerY = 8;
int speedX = 300;
int speedY = 300;
int dirX = 0;
int dirY = 1;
int playerW = TILE_SIZE;
int playerH = TILE_SIZE;
int jumpConter = INITIAL_MAX_JUMP_HEIGHT;*/

class Mob
{
public:
    int x;
    int y;
    int speedX;
    int speedY;
    int dirX;
    int dirY;
    int width = TILE_SIZE;
    int height = TILE_SIZE;
    int jumpConter = INITIAL_MAX_JUMP_HEIGHT;
    sf::RectangleShape sprite;
    int tipo;
    Mob(int x, int y, int speedX, int speedY, int dirX, int dirY, int width, int height, sf::RectangleShape &sprite):
        x(x), y(y), speedX(speedX), speedY(speedY), dirX(dirX), dirY(dirY), width(width), height(height), sprite(sprite)
    {

    }
};

sf::RectangleShape player(sf::Vector2f(TILE_SIZE, TILE_SIZE));
sf::RectangleShape enemy(sf::Vector2f(TILE_SIZE, TILE_SIZE));

Mob playerMob(2, 12, 300, 300, 0, 1, TILE_SIZE, TILE_SIZE, player);
Mob enemyMob(12, 6, 100, 300, -1, 1, TILE_SIZE, TILE_SIZE, enemy);

int map[FIELD_HEIGHT][FIELD_WIDTH] = 
{
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1}
};

sf::VideoMode vm(WINDOW_WIDTH, WINDOW_HEIGHT);
sf::RenderWindow window(vm, "Hello SFML", sf::Style::Default);

float position(int pos)
{
    return (float)(pos * TILE_SIZE+(TILE_SIZE/2));
}

bool colide(float x, float y)
{
    int mapX = (int)std::floor(x / (float)TILE_SIZE);
    int mapY = (int)std::floor(y / (float)TILE_SIZE);

    if (map[mapY][mapX] == 1)
    {
        std::cout<<"Collision: " << mapX << ", " << mapY << std::endl;
        return true;
    }
    return false;
}

void input()
{
    sf::Event evt;

    while (window.pollEvent(evt))
    {
        if (evt.key.code == sf::Keyboard::Escape
            || evt.type == sf::Event::Closed)
            window.close();
        
        if (evt.type == sf::Event::KeyPressed)
        {
            if (evt.key.code == sf::Keyboard::Up && playerMob.jumpConter > 0)
                playerMob.dirY = -1;
            if (evt.key.code == sf::Keyboard::Down)
                playerMob.dirY = 1;
            if (evt.key.code == sf::Keyboard::Left)
                playerMob.dirX = -1;
            if (evt.key.code == sf::Keyboard::Right)
                playerMob.dirX = 1;
        }
        if (evt.type == sf::Event::KeyReleased)
        {
            if (evt.key.code == sf::Keyboard::Up)
            {
                playerMob.dirY = 0;
                playerMob.jumpConter = INITIAL_MAX_JUMP_HEIGHT;
            }
            if (evt.key.code == sf::Keyboard::Down)
                playerMob.dirY = 0;
            if (evt.key.code == sf::Keyboard::Left)
                playerMob.dirX = 0;
            if (evt.key.code == sf::Keyboard::Right)
                playerMob.dirX = 0;
        }
    }
}

float rect(int dir)
{
    if (dir > 0)
        return TILE_SIZE / 2;
    return -1 * (TILE_SIZE / 2);
}

void m(Mob &mob, float deltaTime)
{
    float posX = (mob.speedX * deltaTime) * mob.dirX;
    float posY = (mob.speedY * deltaTime) * mob.dirY;

    for (int i = 0; i <= mob.height; i += TILE_SIZE)
    {
        if (colide(posX + mob.sprite.getPosition().x + rect(mob.dirX), mob.sprite.getPosition().y - (mob.height/2) + i))
        {
            posX = 0;
        }
    }

    for (int i = 0; i <= mob.width; i += TILE_SIZE)
    {
        if (colide(mob.sprite.getPosition().x  - (mob.width/2) + i, posY + mob.sprite.getPosition().y + rect(mob.dirY)))
        {
            posY = 0;
        }
    }

    if (mob.dirY < 0 && mob.jumpConter > 0)
    {
        mob.jumpConter--;
    }
    else
    {
        mob.dirY = 1;
    }

    mob.sprite.move(sf::Vector2f(posX, posY));
}

void update(float deltaTime)
{
    m(playerMob, deltaTime);
    m(enemyMob, deltaTime);


    if (playerMob.sprite.getGlobalBounds().intersects(enemyMob.sprite.getGlobalBounds()))
    {
        window.close();
        std::cout<<"Game Over!"<<std::endl;
    }
}

void render()
{
    for (int y = 0; y < FIELD_HEIGHT; y++)
    {
        for (int x = 0; x < FIELD_WIDTH; x++)
        {
            int content = map[y][x];

            if (content == 0)
            {
                sf::RectangleShape r(sf::Vector2f(TILE_SIZE, TILE_SIZE));
                r.setFillColor(sf::Color::Black);
                r.setOrigin(TILE_SIZE/2, TILE_SIZE/2);
                r.setOutlineColor(sf::Color::White);
                r.setOutlineThickness(1.0f);
                r.setPosition(position(x), position(y));
                window.draw(r);
            }

            if (content == 1)
            {
                sf::RectangleShape r(sf::Vector2f(TILE_SIZE, TILE_SIZE));
                r.setFillColor(sf::Color::Blue);
                r.setOrigin(TILE_SIZE/2, TILE_SIZE/2);
                r.setOutlineColor(sf::Color::White);
                r.setOutlineThickness(1.0f);
                r.setPosition(position(x), position(y));
                window.draw(r);
            }
        }
    }

    window.draw(enemyMob.sprite);
    window.draw(playerMob.sprite);
}

int main()
{
    sf::Clock clock;
    
    playerMob.sprite.setFillColor(sf::Color::Green);
    playerMob.sprite.setOrigin(TILE_SIZE/2, TILE_SIZE/2);
    playerMob.sprite.setOutlineColor(sf::Color::White);
    playerMob.sprite.setOutlineThickness(1.0f);
    playerMob.sprite.setPosition(position(playerMob.x), position(playerMob.y)-1.0f);

    enemyMob.sprite.setFillColor(sf::Color::Red);
    enemyMob.sprite.setOrigin(TILE_SIZE/2, TILE_SIZE/2);
    enemyMob.sprite.setOutlineColor(sf::Color::White);
    enemyMob.sprite.setOutlineThickness(1.0f);
    enemyMob.sprite.setPosition(position(enemyMob.x), position(enemyMob.y)-1.0f);

    playerMob.tipo = 0;
    enemyMob.tipo = 1;

    while (window.isOpen())
    {
        input();

        sf::Time dt = clock.restart();
        update(dt.asSeconds());

        window.clear(sf::Color::Black);
        render();
        window.display();
    }
    return 0;
}
