#include "mine.hpp"

Mine::Mine()
{
	new_position();

	rectangle.w = 5;
	rectangle.h = 5;

	avoid = false;
}

void Mine::draw(SDL_Renderer* renderer)
{
	if (avoid) SDL_SetRenderDrawColor(renderer, ORANGE, 255);
	else SDL_SetRenderDrawColor(renderer, BLACK, 255);
	SDL_RenderFillRect(renderer, &rectangle);
}

void Mine::new_position()
{
	int rand_x = rand() % SCREEN_WIDTH;
	int rand_y = rand() % SCREEN_HEIGHT;
	p = Vector(rand_x, rand_y);

	rectangle.x = p.x;
	rectangle.y = p.y;
}

Vector& Mine::get()
{
	return p;
}

bool Mine::is_avoid()
{
	return avoid;
}

void Mine::set_avoid(bool avoid)
{
	this->avoid = avoid;
}
