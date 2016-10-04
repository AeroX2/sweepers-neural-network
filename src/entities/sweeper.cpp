#include "sweeper.hpp"

Sweeper::Sweeper(Vector p, Brain brain)
{
	this->p = p;
	this->brain = brain;

	rectangle.x = p.x;
	rectangle.y = p.y;
	rectangle.w = 10;
	rectangle.h = 10;

	rotation = 0.0;
	speed = 50.0;
	best = false;
}

void Sweeper::update(Mine mine)
{
	Vector normalised_vector = (p - mine.get()).normalise();
	Vector normalised_velocity = v;

	Matrix matrix = Matrix(1,6);
	matrix.set(0,0,normalised_vector.x); 
	matrix.set(0,1,normalised_vector.y);
	matrix.set(0,2,normalised_velocity.x);
	matrix.set(0,3,normalised_velocity.y);
	matrix.set(0,4,mine.is_avoid());
	matrix.set(0,5,-1.0); //faster than add_bias (probably)
	Matrix output = brain.update(matrix);

	if (output.size() != BRAIN_OUTPUT_LEN+1) throw runtime_error("Output of matrix does not match expected");

	float ltrack = output.get(0,0);
	float rtrack = output.get(0,1);
	float rotation_force = ltrack - rtrack; 

	if (rotation_force > MAX_SWEEPER_TURN_RATE) rotation_force = MAX_SWEEPER_TURN_RATE;
	if (rotation_force < -MAX_SWEEPER_TURN_RATE) rotation_force = -MAX_SWEEPER_TURN_RATE;

	rotation += rotation_force;

	float speed = ltrack + rtrack;
	//float speed = CONTROL_SWEEPER_SPEED;
	//float rotation = (output.get(0,0) - 0.5)*2*M_PI;
	v.x = cos(rotation);
	v.y = sin(rotation);

	/*if (v.x > MAX_SWEEPER_SPEED) v.x = MAX_SWEEPER_SPEED; 
	else if (v.x < -MAX_SWEEPER_SPEED) v.x = -MAX_SWEEPER_SPEED; 
	if (v.y > MAX_SWEEPER_SPEED) v.y = MAX_SWEEPER_SPEED; 
	else if (v.y < -MAX_SWEEPER_SPEED) v.y = -MAX_SWEEPER_SPEED; */

	p += v * speed;
	rectangle.x = round(p.x);
	rectangle.y = round(p.y);
}

void Sweeper::draw(SDL_Renderer* renderer)
{
	if (is_best()) SDL_SetRenderDrawColor(renderer, RED, 255);
	else SDL_SetRenderDrawColor(renderer, BLACK, 255);
	SDL_RenderDrawRect(renderer, &rectangle);
}

void Sweeper::new_position()
{
	int rand_x = rand() % SCREEN_WIDTH;
	int rand_y = rand() % SCREEN_HEIGHT;
	p = Vector(rand_x, rand_y);
	rotation = Utils::random_range(0,2*M_PI);
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

bool Sweeper::is_best()
{
	return best;
}

void Sweeper::set_best(bool best)
{
	this->best = best;
}

Sweeper* Sweeper::create(Vector p, Brain brain)
{
	return new Sweeper(p, brain);
}

