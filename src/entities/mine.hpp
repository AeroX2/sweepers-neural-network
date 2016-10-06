#ifndef MINE_H
#define MINE_H

#include <SDL2/SDL.h>

#include "../constants.hpp"
#include "vector.hpp"

class Mine
{
	public:
		Mine();
		void draw(SDL_Renderer* renderer);
		void new_position();
		Vector& get();

		bool is_avoid();
		void set_avoid(bool avoid);
	private:
		Vector p;
		SDL_Rect rectangle;
		bool avoid;
};

#endif
