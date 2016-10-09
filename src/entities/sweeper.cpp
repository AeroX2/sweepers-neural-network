#include "sweeper.hpp"

Sweeper::Sweeper(Vector p, Brain brain) : p(p), brain(brain)
{
	//this->p = p;
	//this->brain = brain;

	rectangle.x = p.x;
	rectangle.y = p.y;
	rectangle.w = 10;
	rectangle.h = 10;

	rotation = 0.0;
	best = false;
}

void Sweeper::update(Mine mine)
{
	Matrix output = update_brain(mine);
	float ltrack = output.get(0,0);
	float rtrack = output.get(0,1);
	update_tank(ltrack, rtrack);
}

Matrix Sweeper::update_brain(Mine mine)
{
	Vector normalised_mine = mine.get();

	Vector normalised_minus = (p - mine.get()).normalise();
	Vector normalised_velocity = v;

	normalised_mine.x = (normalised_mine.x) / (SCREEN_WIDTH);
	normalised_mine.y = (normalised_mine.y) / (SCREEN_HEIGHT);

	Matrix matrix = Matrix(1,6);
	matrix.set(0,0,normalised_minus.x);
	matrix.set(0,1,normalised_minus.y);
	matrix.set(0,2,normalised_velocity.x);
	matrix.set(0,3,normalised_velocity.y);
	matrix.set(0,4,mine.is_avoid());
	matrix.set(0,5,-1.0); //faster than add_bias (probably)
	Matrix output = brain.update(matrix);

	if (output.size() != BRAIN_OUTPUT_LEN+1) throw runtime_error("Output of matrix does not match expected");
	return output;
}

void Sweeper::update_tank(float ltrack, float rtrack)
{
	ltrack = Utils::constrain(ltrack, 0, 1);
	rtrack = Utils::constrain(rtrack, 0, 1);
	float rotation_force = (rtrack - ltrack) ;// (rectangle.w) * (2*M_PI);

	if (rotation_force > MAX_SWEEPER_TURN_RATE) rotation_force = MAX_SWEEPER_TURN_RATE;
	if (rotation_force < -MAX_SWEEPER_TURN_RATE) rotation_force = -MAX_SWEEPER_TURN_RATE;

	rotation += rotation_force;

	float speed = (ltrack + rtrack) / 2;
	//float speed = CONTROL_SWEEPER_SPEED;
	//float rotation = (output.get(0,0) - 0.5)*2*M_PI;
	v.x = cos(rotation);
	v.y = sin(rotation);

	/*if (v.x > MAX_SWEEPER_SPEED) v.x = MAX_SWEEPER_SPEED;
	else if (v.x < -MAX_SWEEPER_SPEED) v.x = -MAX_SWEEPER_SPEED;
	if (v.y > MAX_SWEEPER_SPEED) v.y = MAX_SWEEPER_SPEED;
	else if (v.y < -MAX_SWEEPER_SPEED) v.y = -MAX_SWEEPER_SPEED; */

	p += v * speed * 2;
	rectangle.x = round(p.x) - rectangle.w / 2;
	rectangle.y = round(p.y) - rectangle.h / 2;
}

void Sweeper::draw(SDL_Renderer* renderer)
{
	if (is_best()) SDL_SetRenderDrawColor(renderer, RED, 255);
	else SDL_SetRenderDrawColor(renderer, BLACK, 255);

	//TODO Change drawing code to draw from center outwards
	//TODO Change drawing code to apply rotation
	SDL_RenderDrawRect(renderer, &rectangle);
}

void Sweeper::new_position()
{
	int rand_x = Utils::random_range_int(0, SCREEN_WIDTH);
	int rand_y = Utils::random_range_int(0, SCREEN_HEIGHT);
	p = Vector(rand_x, rand_y);
	rotation = Utils::random_range_float(0,2*M_PI);
}

Vector& Sweeper::get()
{
	return p;
}

SDL_Rect& Sweeper::get_rect()
{
	return rectangle;
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

float& Sweeper::get_fitness()
{
	return brain.get_fitness();
}

void Sweeper::set_fitness(float fitness)
{
	brain.set_fitness(fitness);
}

Sweeper* Sweeper::create(Vector p, Brain brain)
{
	return new Sweeper(p, brain);
}

