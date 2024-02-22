#include "main.hpp"

#ifdef __EMSCRIPTEN__
#include "emscripten.h"
#include "emscripten/html5.h"

void run()
{
	Main::get_instance().run();
}
#endif

//Windows needs argc and argv to compile
int main(int argc, char* argv[])
{
	if (Main::get_instance().init())
	{
	    cerr << "Error in initialising window\n";
	}
	else
	{
#ifdef __EMSCRIPTEN__
        emscripten_set_main_loop(run, 0, 1);
#else
        Main::get_instance().run();
#endif
	}
	return 0;
}

Main::Main()
{
	window = NULL;
	renderer = NULL;
	font = NULL;

	running = true;
	fast = false;
	best = false;
	interactive = false;
}

void Main::run()
{
	double current_time, delta;
	current_time = SDL_GetTicks();

#ifndef __EMSCRIPTEN__
	while (running)
	{
#endif
		double last_time = current_time;

		//if (Controller::generation >= 300) break;

		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT) running = false;
			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_f)
				{
					cout << "F key pressed\n";
					Plotter::set_dirty();
					fast = !fast;
				}
				else if (e.key.keysym.sym == SDLK_b)
				{
					cout << "B key pressed\n";
					best = !best;
				}
				else if (e.key.keysym.sym == SDLK_i)
				{
					cout << "I key pressed\n";
					interactive = !interactive;
				}
				else if (e.key.keysym.sym == SDLK_c)
				{
					cout << "C key pressed\n";
					logic.clear_mines();
				}
			}
			if (e.type == SDL_MOUSEBUTTONDOWN && !fast)
			{
				logic.mouse_down(e.button.x, e.button.y, e.button.button == SDL_BUTTON_RIGHT);
			}

		}

#ifdef __EMSCRIPTEN__
		    for (int i = 0; i < (fast ? 500 : 1); i++)
#endif
		    logic.update();

		if (fast)
		{
			if (Plotter::is_dirty())
			{
				SDL_SetRenderDrawColor(renderer,WHITE,0);
				SDL_RenderClear(renderer);

				Plotter::draw(renderer);

				SDL_RenderPresent(renderer);
			}
		}
		else
		{
			SDL_SetRenderDrawColor(renderer,WHITE,0);
			SDL_RenderClear(renderer);

			logic.draw(renderer);

			SDL_RenderPresent(renderer);

#ifndef __EMSCRIPTEN__
			current_time = SDL_GetTicks();
			delta = (current_time - last_time);
			if (delta < FRAMERATE) SDL_Delay(FRAMERATE - delta);
#endif
		}

#ifndef __EMSCRIPTEN__
	}
#endif

#ifdef __EMSCRIPTEN__
	if (!running)
	{
        emscripten_cancel_main_loop();
		destroy();
	}
#else
	destroy();
#endif
}

bool Main::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) return true;
#ifdef __EMSCRIPTEN__
    double canvasWidth, canvasHeight;
    emscripten_get_element_css_size("#canvas", &canvasWidth, &canvasHeight);
	window = SDL_CreateWindow("Neural Network Sweepers", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, canvasWidth, canvasHeight, SDL_WINDOW_SHOWN);
#else
	window = SDL_CreateWindow("Neural Network Sweepers", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
#endif
	if (window == NULL) {
		cout << "Couldn't create SDL window\n";
		return true;
	}
	renderer = SDL_CreateRenderer(window,0,SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		cout << "Couldn't initialize render engine\n";
		return true;
	}
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	if (TTF_Init() < 0) {
		cout << "Couldn't initialize font engine\n";
		return true;
	}
	font = TTF_OpenFont("data/arial.ttf", 12);
	if (font == NULL) {
		cout << "Couldn't read font\n";
		return true;
	}

	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
		cout << "Couldn't initialize test image\n";
		return true;
	}

	if (Config::read_from_file("data/config.txt")) cout << "Using values from files\n";
	else cout << "Failed to read from file, using defaults\n";

	Plotter::init(10);
	Plotter::new_line(BLACK);
	Plotter::new_line(RED);
	if (CONTROL_SWEEPER) Plotter::new_line(PURPLE);

	logic.init();

	return false;
}

void Main::destroy()
{
	Assets::destroy_textures();
	TTF_CloseFont(font);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Main::draw_font_p(string message, int x, int y)
{
	SDL_Color color = {BLACK, 255};

	SDL_Surface* text_surface = TTF_RenderText_Blended(font, message.c_str(), color);
	if (text_surface == NULL)
	{
		cerr << "Couldn't create text to draw\n";
		return;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	if (texture == NULL)
	{
		 cerr << "Unable to create texture from rendered text\n";
		 return;
	}
	int width = 0;
	int height = 0;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	SDL_Rect offset = {x, y, width, height};

	SDL_RenderCopy(renderer, texture, NULL, &offset);

	SDL_FreeSurface(text_surface);
	SDL_DestroyTexture(texture);
}

Main& Main::get_instance()
{
	static Main main;
	return main;
}

void Main::draw_font(string message, int x, int y)
{
	get_instance().draw_font_p(message, x, y);
}

SDL_Renderer* Main::get_renderer()
{
	return get_instance().renderer;
}

bool Main::is_best()
{
	return get_instance().best;
}


bool Main::is_interactive()
{
	return get_instance().interactive;
}
