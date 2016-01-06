#ifndef SWEEPER_H
#define SWEEPER_H

#include <SDL2/SDL.h>

#include "../constants.hpp"
#include "vector.hpp"
#include "../network/brain.hpp"

class Vector;

class Sweeper
{
	public:
		Sweeper(Vector p, Brain brain);
		void update(Vector mine_location, double delta);
		void draw(SDL_Renderer* renderer);
		void new_position();

		Vector& get();
		void set(Vector p);
		Brain& get_brain();
		void set_brain(Brain b);
	private:
		double speed;
		double rotation;
		Vector v;
		Vector p;
		SDL_Rect rectangle;
		Brain brain;
};

#endif
