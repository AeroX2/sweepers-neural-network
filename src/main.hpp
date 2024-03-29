#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include "SDL.h"
#include "SDL_ttf.h"

#include "constants.hpp"
#include "config.hpp"
#include "assets.hpp"
#include "logic.hpp"

using namespace std;

class Main
{
	public:
		static Main& get_instance();
		static void draw_font(string message, int x, int y);
		static SDL_Renderer* get_renderer();
		static bool is_best();
		static bool is_interactive();
		bool init();
		void run();
	private:
		Main();

		void destroy();
		void draw_font_p(string message, int x, int y);

		SDL_Window* window;
		SDL_Renderer* renderer;
		TTF_Font* font;
		Logic logic;

		bool running;
		bool fast;
		bool best;
		bool interactive;
};

#endif
