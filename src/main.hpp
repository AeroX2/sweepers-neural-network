#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "constants.hpp"
#include "config.hpp"
#include "logic.hpp"

using namespace std;

class Main
{
	public:
		static Main get_instance();
	private:
		Main();

		bool init();
		void run();
		void destroy();
		void draw_font(string message, int x, int y);

		SDL_Window* window;
		SDL_Renderer* renderer;
		TTF_Font* font;
		Logic logic;

		bool running;
		bool fast;
		bool best;
};

#endif
