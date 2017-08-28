#ifndef MINE_H
#define MINE_H

#include "SDL.h"

#include "../constants.hpp"
#include "../utils.hpp"
#include "entity.hpp"

class Mine : public Entity
{
	public:
		Mine();
		Mine(int x, int y);
		void new_position();

		bool is_avoid();
		void set_avoid(bool avoid);

		bool is_dead();
		void set_dead(bool dead);
	private:
		bool avoid;
		bool dead;
};

#endif
