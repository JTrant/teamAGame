#include "missile.h"
#include <SDL.h>
#include <iostream>
#include <cmath>
#include <SDL_image.h>

Missile::Missile(int damage, int blast_radius, double x, double y, double xvel, double yvel, SDL_Texture* s, SDL_Renderer* gRenderer) :
	damage{ damage }, blast_radius{ blast_radius }, xPos{ x }, yPos{ y },
	xVel { xvel }, yVel{ yvel }, width{ MISSILE_SIZE }, height{ MISSILE_SIZE / 4}
{
	sprite = s;

	velocity_magnitude = sqrt(pow(xVel, 2) + pow(yVel, 2));

	pitch = atan(yVel / xVel);
	if (xVel < 0)
	{
		pitch = M_PI + pitch;
	}
	std::cout << xVel << " " << yVel << " " << pitch << std::endl;
	air_time = 0;
	last_move = SDL_GetTicks();
}

SDL_Texture* Missile::loadImage(std::string fname, SDL_Renderer *gRenderer) {
	SDL_Texture* newText = nullptr;

	SDL_Surface* startSurf = IMG_Load(fname.c_str());
	if (startSurf == nullptr) {
		std::cout << "Unable to load image " << fname << "! SDL Error: " << SDL_GetError() << std::endl;
		return nullptr;
	}

	newText = SDL_CreateTextureFromSurface(gRenderer, startSurf);
	if (newText == nullptr) {
		std::cout << "Unable to create texture from " << fname << "! SDL Error: " << SDL_GetError() << std::endl;
	}

	SDL_FreeSurface(startSurf);

	return newText;
}

void Missile::renderMissile(SDL_Renderer* gRenderer)
{
	SDL_Rect missile_location = {(int) xPos, (int) yPos, MISSILE_SIZE, MISSILE_SIZE / 4};
	SDL_RenderCopyEx(gRenderer, sprite, nullptr, &missile_location, pitch * 180.0 / M_PI, nullptr, SDL_FLIP_NONE);
}

void Missile::move(double x_scroll)
{
	time_since_move = SDL_GetTicks() - last_move;

	xPos += (double) time_since_move * xVel / 1000 - x_scroll;
	yPos += (double) time_since_move * yVel / 1000;
	air_time += time_since_move;

	last_move = SDL_GetTicks();
}

bool Missile::checkCollision(Missile *m){

    if (this->getX() + this->getWidth() < m->getX() || this->getX() > m->getX() + m->getWidth())
        return false;
    if (this->getY() + this->getHeight() < m->getY() || this->getY() > m->getY() + m->getHeight())
        return false;
    return true;

}

bool Missile::checkCollision(Bullet *b){

    if (this->getX() + this->getWidth() < b->getX() || this->getX() > b->getX() + b->getWidth())
        return false;
    if (this->getY() + this->getHeight() < b->getY() || this->getY() > b->getY() + b->getHeight())
        return false;
    return true;

}

// Calculates how far the entity is to this missile,
// using the basic distance formula for two points in a X and Y plane
double Missile::calculate_distance(double entity_x, double entity_y)
{
	return abs(sqrt(pow(xPos - entity_x, 2) + pow(yPos - entity_y, 2)));
}

// Calculates how much damage the warhead will do to entity,
// depending on the entity's distance to the warhead
double Missile::calculate_damage(double entity_x, double entity_y)
{
	double distance = calculate_distance(entity_x, entity_y);
	if(this->missType < 4){
		return blast_radius / pow(distance, 2) * damage;
	}
	else{
		return (blast_radius / pow(distance, 2) * damage) * 1.5;//red missiles do x1.5 damage
	}
	
}

bool Missile::ricochet()
{
	return true;
}

// Accessor methods

int Missile::getX()
{
	return xPos;
}

int Missile::getY()
{
	return yPos;
}

int Missile::getWidth()
{
	return width;
}

int Missile::getHeight()
{
	return height;
}

int Missile::getXVel()
{
	return xVel;
}

int Missile::getYVel()
{
	return yVel;
}

int Missile::get_blast_radius()
{
	return blast_radius;
}