#ifndef ENTITY_H
#define ENTITY_H

#define _USE_MATH_DEFINES
#include <cmath> 
#include "SDL.h"

//Windows MSYS
#if defined(_WIN32)
	#include <stdexcept>
#endif

#include "../network/brain.hpp"
#include "../constants.hpp"
#include "../assets.hpp"
#include "vector.hpp"

class Entity
{
	public:
		Entity(Vector p, string path);
		virtual ~Entity() {};
		virtual void draw(SDL_Renderer* renderer);

		Vector& get();
		SDL_Rect& get_rect();

		void set_color(int r, int g, int b);
	protected:
		double rotation;

		Vector v;
		Vector p;
		SDL_Rect rectangle;
		SDL_Color color;
		SDL_Texture* texture;
};

#endif
