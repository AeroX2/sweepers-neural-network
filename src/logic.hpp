#ifndef LOGIC_H
#define LOGIC_H

#include <memory>

//Windows MSYS
#if defined(_WIN32)
	#include <string>
	#include <sstream>
	template<typename T> std::string to_string(const T& n)
	{
		std::ostringstream stm;
		stm << n;
		return stm.str();
	}
#endif

#include "controller.hpp"
#include "entities/mine.hpp"
#include "entities/sweeper.hpp"
#include "entities/control_sweeper.hpp"
#include "network/brain.hpp"
#include "network/matrix.hpp"

using namespace std;

class Logic
{
	public:
		Logic();
		~Logic();
		void init();
		void update();
		void draw(SDL_Renderer* renderer);
		void clear_mines();
		void mouse_down(int x, int y, bool avoid);
	private:
		vector<reference_wrapper<Sweeper>> sweepers;
		vector<Mine> mines;
		int ticks;
		float max_fitness;

		Control_Sweeper* control_sweeper;
		Sweeper* best_sweeper;
};

#endif
