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
	float a = atan2(temp.y, temp.x);
	float d = temp.distance();
	float w = rectangle.w;

	float ltrack, rtrack;
	float rotation_to = a - rotation;
	if (rotation_to > 0)
	{
		ltrack = 1;
		rtrack = (4*M_PI*d+w*a)/(4*M_PI*d-w*a);
	}
	else
	{
		ltrack = (4*M_PI*d-w*a)/(4*M_PI*d+w*a);
		rtrack = 1;
	}
	cout << ltrack << " " << rtrack << '\n';

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
