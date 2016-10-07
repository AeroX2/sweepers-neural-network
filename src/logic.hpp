#ifndef LOGIC_H
#define LOGIC_H

#include <memory>
#include "entities/mine.hpp"
#include "entities/sweeper.hpp"
#include "entities/control_sweeper.hpp"
#include "network/brain.hpp"
#include "network/matrix.hpp"

#include "controller.hpp"

struct SDL_Renderer;

using namespace std;

class Logic
{
	public:
		Logic();
		~Logic();
		void update();
		void draw(SDL_Renderer* renderer);
	private:
		vector<reference_wrapper<Sweeper>> sweepers;
		vector<Mine> mines;
		int ticks;
		float max_fitness;

		Control_Sweeper* control_sweeper = NULL;
		Sweeper* best_sweeper = NULL;
};

#endif
