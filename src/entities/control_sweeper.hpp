#ifndef CONTROL_SWEEPER_H
#define CONTROL_SWEEPER_H

#include "sweeper.hpp"

class Control_Sweeper : public Sweeper
{
	public:
		Control_Sweeper(Vector p, Brain brain);
		virtual void update(Vector mine_location);
		virtual void draw(SDL_Renderer* renderer);
};

#endif
