#ifndef SWEEPER_H
#define SWEEPER_H

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
#include "entity.hpp"
#include "vector.hpp"
#include "mine.hpp"

class Sweeper : public Entity
{
	public:
		static Sweeper* create(Vector p, Brain& brain);

		virtual void update(Mine mine, Mine avoid_mine);
		Matrix update_brain(Mine mine, Mine avoid_mine);
		void update_tank(float ltrack, float rtrack);

		void new_position();

		Brain& get_brain();
		void set_brain(Brain& b);

		bool is_best();
		void set_best(bool best);

		virtual float& get_fitness();
		virtual void set_fitness(float fitness);
	protected:
		Sweeper(Vector p, Brain& brain);

		bool best;
		Brain brain;
};

#endif
