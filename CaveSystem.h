#ifndef CaveSystem_H
#define CaveSystem_H

#include <SDL.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include "Player.h"
#include "Enemy.h"
#include "missile.h"

class CaveBlock
{
public:
    // absolute coordinates of each CaveBlock
    int CAVE_BLOCK_ABS_X;
    int CAVE_BLOCK_ABS_Y;

    // coordinates of each CaveBlock relative to camera
    int CAVE_BLOCK_REL_X;
    int CAVE_BLOCK_REL_Y;

    int enabled; // Is the cave block going to be visible? 1 = yes, 0 = no
    int isPointy; //Pointy blocks only deal quarty damage to player and enemy

    static const int CAVE_BLOCK_HEIGHT = 20;
    static const int CAVE_BLOCK_WIDTH = 20;
	static const int CAVE_SYSTEM_PIXEL_HEIGHT = 720;
	static const int CAVE_SYSTEM_PIXEL_WIDTH = 4000;
    CaveBlock();
    std::string toString();
};


class PathSequence
{
public:
    int x[CaveBlock::CAVE_SYSTEM_PIXEL_WIDTH / CaveBlock::CAVE_BLOCK_WIDTH];
    int y[CaveBlock::CAVE_SYSTEM_PIXEL_WIDTH / CaveBlock::CAVE_BLOCK_WIDTH];
    int length;

    PathSequence();
};


class CaveSystem
{
public:
    static const int CAVE_SYSTEM_HEIGHT = CaveBlock::CAVE_SYSTEM_PIXEL_HEIGHT / CaveBlock::CAVE_BLOCK_HEIGHT;
    static const int CAVE_SYSTEM_WIDTH = CaveBlock::CAVE_SYSTEM_PIXEL_WIDTH / CaveBlock::CAVE_BLOCK_WIDTH;
	static const int CAVE_SYSTEM_FREQ = 10000;
    
    static int CAVE_START_ABS_X;
    static int CAVE_END_ABS_X; 

    bool isEnabled = false;
    PathSequence path;
    CaveBlock *cave_system[CAVE_SYSTEM_HEIGHT][CAVE_SYSTEM_WIDTH];

    CaveSystem();
    CaveSystem(int camX, int camY, int SCREEN_WIDTH, int difficulty);
    ~CaveSystem();

    void render(SDL_Renderer *gRenderer);
    void moveCaveBlocks(int camX, int camY);
    void checkCollision(Player *p);
    void checkCollision(Enemy *e);
	bool checkCollision(Bullet *b);
	bool checkCollision(Missile *m);
    void render(int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Renderer *gRenderer);
    PathSequence* getPathSequence();
	int getStartX();
	int getEndX();

    SDL_Texture* ceilSprite;
    SDL_Texture* floorSprite;
    int diff;
private:
    void generateRandomCave();
};


#endif
