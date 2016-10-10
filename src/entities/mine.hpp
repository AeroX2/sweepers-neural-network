#ifndef MINE_H
#define MINE_H

#include <SDL2/SDL.h>

#include "../constants.hpp"
#include "../utils.hpp"
#include "entity.hpp"

class Mine : public Entity
{
	public:
		Mine();
		void new_position();

		bool is_avoid();
		void set_avoid(bool avoid);
	private:
		bool avoid;
};

#endif
