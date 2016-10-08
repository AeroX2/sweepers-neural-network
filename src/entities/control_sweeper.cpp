#include "control_sweeper.hpp"

Control_Sweeper::Control_Sweeper(Vector p, Brain brain) : Sweeper(p, brain)
{
	this->p = p;

	rectangle.x = p.x;
	rectangle.y = p.y;
	rectangle.w = 10;
	rectangle.h = 10;

	rotation = 0.0;
	fitness = 0;
}

void Control_Sweeper::update(Mine mine) 
{
	Vector temp = p - mine.get();
	float mine_rotation = atan2(temp.y, temp.x);
	float x = mine_rotation - rotation;

	float ltrack = 0;
	float rtrack = 0;
	if (fabs(x) < 5)
	{
		ltrack = 1;
		rtrack = 1;
	}
	else
	{
		ltrack = cos(x);
		rtrack = sin(x);
	}

	update_tank(ltrack, rtrack);
}

void Control_Sweeper::draw(SDL_Renderer* renderer) 
{
	SDL_SetRenderDrawColor(renderer, PURPLE, 255);
	SDL_RenderFillRect(renderer, &rectangle);
}

float& Control_Sweeper::get_fitness()
{
	return fitness;
}

void Control_Sweeper::set_fitness(float fitness)
{
	this->fitness = fitness;
}

Control_Sweeper* Control_Sweeper::create(Vector p, Brain brain)
{
	return new Control_Sweeper(p, brain);
}
