#include "control_sweeper.hpp"

Control_Sweeper::Control_Sweeper(Vector p, Brain& brain) : Sweeper(p, brain)
{
	fitness = 0;
	set_color(PURPLE);
}

void Control_Sweeper::update(Mine mine)
{
	Vector temp = mine.get() - p;
	float m = atan2(temp.y, temp.x) + (mine.is_avoid() ? M_PI : 0);
	float r = rotation - M_PI;
	float d = temp.distance();

	float a = r - m;
	a += (a>M_PI) ? -2*M_PI : (a<-M_PI) ? 2*M_PI : 0;

	float ltrack;
	float rtrack;
	if (d < 80 && a > -0.1 && a < 0.1)
	{
		ltrack = 1;
		rtrack = 1;
	}
	else if (a < 0)
	{
		ltrack = 1;
		rtrack = (2*d+a)/(2*d-a);
	}
	else
	{
		ltrack = (2*d-a)/(2*d+a);
		rtrack = 1;
	}
	/*cout << (a > 0) << '\n';
	cout << d << " " << a << '\n';
	cout << ltrack << " " << rtrack << '\n';
	cout << "snakes\n";*/
	/*p.x += cos(a);
	p.y += sin(a);
	rectangle.x = round(p.x);
	rectangle.y = round(p.y);*/

	update_tank(ltrack, rtrack);
}

float& Control_Sweeper::get_fitness()
{
	return fitness;
}

void Control_Sweeper::set_fitness(float fitness)
{
	this->fitness = fitness;
}

Control_Sweeper* Control_Sweeper::create(Vector p, Brain& brain)
{
	return new Control_Sweeper(p, brain);
}
