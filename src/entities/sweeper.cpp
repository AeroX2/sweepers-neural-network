#include "sweeper.hpp"

Sweeper::Sweeper(Vector p, Brain brain)
{
	this->p = p;
	this->brain = brain;

	rectangle.w = 10;
	rectangle.h = 10;

	rotation = 0.0;
	speed = 50.0;
}

void Sweeper::update(Vector mine_location, double delta)
{
	Vector normalised_vector = (p - mine_location);
	Matrix matrix = Matrix(1,5);
	matrix.set(0,0,normalised_vector.x); 
	matrix.set(0,1,normalised_vector.y);
	matrix.set(0,2,v.x);
	matrix.set(0,3,v.y);
	matrix.set(0,4,-1); //Bias
	Matrix output = brain.update(matrix);

	float ltrack = output.get(0,0);
	float rtrack = output.get(0,1);
	float rotation_force = ltrack - rtrack; 
	rotation += rotation_force;

	v.x = -sin(rotation);
	v.y = cos(rotation);

	/*if (v.x > MAX_SWEEPER_SPEED) v.x = MAX_SWEEPER_SPEED; 
	else if (v.x < -MAX_SWEEPER_SPEED) v.x = -MAX_SWEEPER_SPEED; 
	if (v.y > MAX_SWEEPER_SPEED) v.y = MAX_SWEEPER_SPEED; 
	else if (v.y < -MAX_SWEEPER_SPEED) v.y = -MAX_SWEEPER_SPEED; */

	float speed = ltrack + rtrack;
	//IDK Will fix
	Vector test = v * speed;
	p += test;

	rectangle.x = round(p.x);
	rectangle.y = round(p.y);
}

void Sweeper::draw(SDL_Renderer* renderer)
{
	SDL_RenderDrawRect(renderer, &rectangle);
}

void Sweeper::new_position()
{
	int rand_x = rand() % SCREEN_WIDTH;
	int rand_y = rand() % SCREEN_HEIGHT;
	this->p = Vector(rand_x, rand_y);
}

Vector& Sweeper::get()
{
	return p;
}

void Sweeper::set(Vector p)
{
	this->p = p;
}

Brain& Sweeper::get_brain()
{
	return brain;
}

void Sweeper::set_brain(Brain brain)
{
	this->brain = brain;
}
