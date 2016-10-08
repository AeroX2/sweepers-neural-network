#ifndef LOGIC_H
#define LOGIC_H

#include <memory>

//Windows MSYS
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	#include <ctime>
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
		void update();
		void draw(SDL_Renderer* renderer);
	private:
		vector<reference_wrapper<Sweeper>> sweepers;
		vector<Mine> mines;
		int ticks;
		float max_fitness;

		Control_Sweeper* control_sweeper;
		Sweeper* best_sweeper;
};

#endif
