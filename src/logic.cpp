#include "logic.hpp"

Logic::Logic()
{
	//Seed random number generator
	srand(time(NULL));	

	int rand_x = 0;
	int rand_y = 0;
	for (int i = 0; i < MINE_LEN; i++)
	{
		Mine new_mine = Mine();
		mines.push_back(new_mine);
	}

	Vector p;
	Brain new_brain;
	for (int i = 0; i < POPULATION; i++)
	{
		rand_x = rand() % SCREEN_WIDTH;
		rand_y = rand() % SCREEN_HEIGHT;
		p = Vector(rand_x, rand_y);
		new_brain = Brain();
		Sweeper* new_sweeper = Sweeper::create(p, new_brain);
		sweepers.push_back(reference_wrapper<Sweeper>(*new_sweeper));
	}

	rand_x = rand() % SCREEN_WIDTH;
	rand_y = rand() % SCREEN_HEIGHT;
	p = Vector(rand_x, rand_y);
	new_brain = Brain();

	Control_Sweeper* temp = Control_Sweeper::create(p,new_brain);
	control_sweeper = temp;	
	//sweepers.push_back(reference_wrapper<Sweeper>(*temp));
	best_sweeper = &sweepers[0].get();

	ticks = 0;
	ticks2 = 0;
	max_fitness = 0;
}

Logic::~Logic()
{
	for (auto reference : sweepers)
	{
		delete &reference.get();
	}
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
			//cout << "distance: " << distance << endl;
			if (distance < HIT_DISTANCE)
			{
				mine.new_position();
				if (mine.is_avoid())  sweeper.get_brain().increase_fitness(-10);
				else sweeper.get_brain().increase_fitness(1);
			}
			else if (distance < min_distance)
			{
				min_distance = distance;
				closest_mine = mine;
			}	
		}
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
		if (sweeper_p.x > SCREEN_WIDTH) sweeper_p.x = -10;
		else if (sweeper_p.x < -10) sweeper_p.x = SCREEN_WIDTH;
		if (sweeper_p.y > SCREEN_HEIGHT) sweeper_p.y = -10;
		else if (sweeper_p.y < -10) sweeper_p.y = SCREEN_HEIGHT;
		//sweeper.set(sweeper_p);
	}

	/*if (ticks2++ > 250)
	{
		ticks2 = 0;
		for (Mine& mine : mines)
		{
			if (mine.is_avoid()) mine.new_position();
		}
	}*/

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
		population = Controller::epoch(population, *control_sweeper);

		//-1 because of Control_Sweeper doesn't deserve a brain
		for (size_t i = 0; i < sweepers.size(); i++) 
		{
			Sweeper& sweeper = sweepers[i].get();
			sweeper.set_brain(population[i]);
			sweeper.get_brain().set_fitness(0);
			sweeper.set_best(false);
			sweeper.new_position();
		}
		for (Mine& mine : mines) mine.new_position();
		//control_sweeper->set_fitness(0);
	}
}

void Logic::draw(SDL_Renderer* renderer)
{
	for (Mine mine : mines) mine.draw(renderer);
	for (auto reference : sweepers) 
	{
		Sweeper& sweeper = reference.get();	
		sweeper.draw(renderer);
	}

	draw_font("Current max fitness: " + to_string(best_sweeper->get_brain().get_fitness()), 10, 10);
	//draw_font("Control sweeper fitness: " + to_string(control_sweeper->get_fitness()), 10, 30);
}
