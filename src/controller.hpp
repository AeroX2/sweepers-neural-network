#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <vector>
#include <algorithm>

//Windows MSYS
#if defined(_WIN32)
	#include <stdexcept>
#endif

#include "constants.hpp"
#include "plotter.hpp"
#include "network/brain.hpp"
#include "entities/control_sweeper.hpp"
#include "utils.hpp"

using namespace std;

class Controller
{
	public:
		static int generation;
		static bool compare_brains(Brain b1, Brain b2);
		static vector<Brain> epoch(vector<Brain> population, Control_Sweeper* control);
		static Brain& roulette(vector<Brain> population, int total_fitness);
		static Brain& tournament(vector<Brain> population);
};

#endif
