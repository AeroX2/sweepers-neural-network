#include "mine.hpp"

Mine::Mine()
{
	rectangle.w = 5;
	rectangle.h = 5;
	avoid = false;

	new_position();
}

void Mine::draw(SDL_Renderer* renderer)
{
	if (avoid) SDL_SetRenderDrawColor(renderer, ORANGE, 255);
	else SDL_SetRenderDrawColor(renderer, BLACK, 255);
	SDL_RenderFillRect(renderer, &rectangle);
}

void Mine::new_position()
{
	int rand_x = Utils::random_range_int(0, SCREEN_WIDTH);
	int rand_y = Utils::random_range_int(0, SCREEN_HEIGHT);
	p = Vector(rand_x, rand_y);

	rectangle.x = p.x - rectangle.w / 2;
	rectangle.y = p.y - rectangle.h / 2;
}

Vector& Mine::get()
{
	return p;
}

SDL_Rect& Mine::get_rect()
{
	return rectangle;
}

bool Mine::is_avoid()
{
	return avoid;
}

void Mine::set_avoid(bool avoid)
{
	this->avoid = avoid;
}
