#include "mine.hpp"

Mine::Mine() : Mine(0,0)
{
	avoid = false;
	dead = false;
	new_position();
}

Mine::Mine(int x, int y) : Entity(Vector(), MINE_IMAGE)
{
	avoid = false;
	dead = false;
	p = Vector(x,y);

	rectangle.x = p.x - rectangle.w / 2;
	rectangle.y = p.y - rectangle.h / 2;
}

void Mine::new_position()
{
    // Offset a little to prevent mines being placed at the edge of the screen
    // where they are unreachable.
	int rand_x = Utils::random_range_int(20, SCREEN_WIDTH-20);
	int rand_y = Utils::random_range_int(20, SCREEN_HEIGHT-20);
	p = Vector(rand_x, rand_y);

	rectangle.x = p.x - rectangle.w / 2;
	rectangle.y = p.y - rectangle.h / 2;
}

bool Mine::is_avoid()
{
	return avoid;
}

void Mine::set_avoid(bool avoid)
{
	this->avoid = avoid;
	if (avoid) set_color(ORANGE);
	else set_color(BLACK);
}

bool Mine::is_dead()
{
	return dead;
}

void Mine::set_dead(bool dead)
{
	this->dead = dead;
}
