#ifndef missile_H
#define missile_H

#include <SDL.h>
#include <iostream>
#include <cmath>
#include <SDL_image.h>
#include "bullet.h"

class Missile
{
    public:
        static const int MISSILE_SIZE = 75;

        Missile(int damage, int blast_radius, double x, double y, double xvel, double yvel, SDL_Texture* s, SDL_Renderer* gRenderer);

        void renderMissile(SDL_Renderer* gRenderer);

        void move(double x_scroll);

        // Calculates how far the entity is to this missile
		double calculate_distance(double entity_x, double entity_y);

        // Calculates how much damage the warhead will do to entity
		double calculate_damage(double entity_x, double entity_y);

        bool checkCollision(Missile* m);
        bool checkCollision(Bullet *b);

        bool ricochet();

        // Accessor functions:

        int getX();
        int getY();

        int getWidth();
        int getHeight();

        int getXVel();
        int getYVel();

        int get_blast_radius();

        SDL_Texture* sprite;

        SDL_Texture* loadImage(std::string fname, SDL_Renderer *gRenderer);

    private:
        // The following variables are the same as from bullet
        // We could have just used inheritance, but it's too late for that

        // Size of missile
        const int width, height;
        int missType;

        // Position coordinates
        double xPos, yPos;

        // Velocity
        double velocity_magnitude, xVel, yVel;

        // Velocity direction in radians
        double pitch;

        // Timing
        int time_since_move;
        int last_move;

        // Time the projectile has been in the air
        double air_time;

        // Missile specific variables:

        // Amount of damage the warhead deals at the center of the blast radius
		int damage;

        // Radius where most damage is caused by the warhead
		int blast_radius;
};

#endif