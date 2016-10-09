#include "logic.hpp"
#include "main.hpp"

Logic::Logic()
{
	ticks = 0;
	max_fitness = 0;
}

Logic::~Logic()
{
	for (auto reference : sweepers)
	{
		delete &reference.get();
	}
}

void Logic::init()
{
	for (int i = 0; i < MINE_LEN; i++)
	{
		Mine new_mine = Mine();
		if (i < MINE_LEN / 2) new_mine.set_avoid(true);
		mines.push_back(new_mine);
	}

	int rand_x;
	int rand_y;
	Vector p;
	Brain new_brain;

	for (int i = 0; i < POPULATION; i++)
	{
		rand_x = Utils::random_range_int(0, SCREEN_WIDTH);
		rand_y = Utils::random_range_int(0, SCREEN_HEIGHT);
		p = Vector(rand_x, rand_y);
		new_brain = Brain();
		Sweeper* new_sweeper = Sweeper::create(p, new_brain);
		sweepers.push_back(reference_wrapper<Sweeper>(*new_sweeper));
	}

	rand_x = Utils::random_range_int(0, SCREEN_WIDTH);
	rand_y = Utils::random_range_int(0, SCREEN_HEIGHT);
	p = Vector(rand_x, rand_y);
	new_brain = Brain();

	control_sweeper = NULL;
	if (CONTROL_SWEEPER)
	{
		Control_Sweeper* temp = Control_Sweeper::create(p,new_brain);
		control_sweeper = temp;
		sweepers.push_back(reference_wrapper<Sweeper>(*temp));
	}

	//TODO Multiple best sweepers
	//TODO Worst and average sweepers?
	best_sweeper = &sweepers[0].get();
}

void Logic::update()
{
	for (auto reference : sweepers)
	{
		Sweeper& sweeper = reference.get();
		Vector& sweeper_p = sweeper.get();

		Mine closest_mine = mines[0];
		Vector mine_p = closest_mine.get();

		float min_distance = (mine_p - sweeper_p).distance();

		for (Mine& mine : mines)
		{
			mine_p = mine.get();
			float distance = (mine_p - sweeper_p).distance();
			/*if (mine_p.x - 50 < sweeper_p.x &&
				mine_p.x + 50 > sweeper_p.x &&
				mine_p.y - 50 < sweeper_p.y &&
				mine_p.y + 50 > sweeper_p.y)
			{*/
			//cout << "distance: " << distance << '\n';
			if (distance < HIT_DISTANCE)
			{
				mine.new_position();
				if (mine.is_avoid()) sweeper.get_fitness() *= PUNISHMENT;
				else sweeper.get_fitness() += REWARD;
			}
			else if (distance < min_distance)
			{
				min_distance = distance;
				closest_mine = mine;
			}
		}

		//Control sweeper has a separate fitness to the brain
		if (sweeper.get_brain().get_fitness() > max_fitness)
		{
			max_fitness = sweeper.get_brain().get_fitness();
			for (auto reference : sweepers)
			{
				Sweeper& sweeper2 = reference.get();
				sweeper2.set_best(false);
			}
			sweeper.set_best(true);
			best_sweeper = &sweeper;
		}
		sweeper.update(closest_mine);

		sweeper_p = sweeper.get();
		SDL_Rect r = sweeper.get_rect();
		if (sweeper_p.x > SCREEN_WIDTH+r.w/2) sweeper_p.x = -r.w/2;
		else if (sweeper_p.x < -r.w/2) sweeper_p.x = SCREEN_WIDTH+r.w/2;
		if (sweeper_p.y > SCREEN_HEIGHT+r.h/2) sweeper_p.y = -r.h/2;
		else if (sweeper_p.y < -r.h/2) sweeper_p.y = SCREEN_HEIGHT+r.h/2;
		//sweeper.set(sweeper_p);
	}

	if (ticks++ > EPOCH_TICK_OVER)
	{
		ticks = 0;
		max_fitness = 0;
		vector<Brain> population = vector<Brain>();
		for (auto reference : sweepers)
		{
			Sweeper& sweeper = reference.get();
			population.push_back(sweeper.get_brain());
		}
		population = Controller::epoch(population, control_sweeper);

		//-1 because of Control_Sweeper doesn't deserve a brain
		for (size_t i = 0; i < sweepers.size() - CONTROL_SWEEPER; i++)
		{
			Sweeper& sweeper = sweepers[i].get();
			sweeper.set_brain(population[i]);
			sweeper.set_fitness(0);
			sweeper.set_best(false);
			sweeper.new_position();
		}
		for (Mine& mine : mines) mine.new_position();
		if (CONTROL_SWEEPER) control_sweeper->set_fitness(0);
	}
}

void Logic::draw(SDL_Renderer* renderer)
{
	for (Mine mine : mines) mine.draw(renderer);
	for (auto reference : sweepers)
	{
		Sweeper& sweeper = reference.get();
		if (!Main::is_best() || sweeper.is_best()) sweeper.draw(renderer);
	}

	Main::draw_font("Current max fitness: " + to_string(best_sweeper->get_fitness()), 10, 10);
	//Main::draw_font("Current worst fitness: " + to_string(worst_sweeper->get_fitness()), 10, 30);
	//Main::draw_font("Current average fitness: " + to_string(average_sweeper->get_fitness()), 10, 50);
	if (CONTROL_SWEEPER) Main::draw_font("Control sweeper fitness: " + to_string(control_sweeper->get_fitness()), 10, 30);
	Main::draw_font("Press F to fast forward", 10, 70);
	Main::draw_font("Press B to see only the best", 10, 90);
}
