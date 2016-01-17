#include "control_sweeper.hpp"

Control_Sweeper::Control_Sweeper(Vector p, Brain brain) : Sweeper(p, brain)
{
	this->p = p;

	rectangle.w = 10;
	rectangle.h = 10;

	rotation = 0.0;
	speed = 1.5;
}

void Control_Sweeper::update(Vector mine_location) 
{
	cout << "weebbbbbb" << endl;
	rotation = atan2(mine_location.y, mine_location.y);

	v.x = -sin(rotation);
	v.y = cos(rotation);

	//IDK Will fix
	Vector test = v * speed;
	p += test;

	rectangle.x = round(p.x);
	rectangle.y = round(p.y);

	cout << "weebbbbbb";
}

void Control_Sweeper::draw(SDL_Renderer* renderer) 
{
	cout << "noo" << endl;
	SDL_SetRenderDrawColor(renderer, PURPLE, 255);
	SDL_RenderFillRect(renderer, &rectangle);
}
