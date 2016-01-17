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
		Sweeper new_sweeper = Sweeper(p, new_brain);
		sweepers.push_back(new_sweeper);
	}
	//Control_Sweeper control_sweeper = Control_Sweeper(p, new_brain);
	//sweepers.push_back(&control_sweeper);

	ticks = 0;
	max_fitness = 0;
}

void Logic::update(double delta)
{
	for (Sweeper &sweeper : sweepers)
	{
		Vector mine_p = mines[0].get();
		Vector sweeper_p = sweeper.get();
		Vector closest_mine = mines[0].get();
		float min_distance = (mine_p - sweeper_p).distance();

		for (Mine& mine : mines)
		{
			mine_p = mine.get();
			if (mine_p.x - 50 < sweeper_p.x && 
				mine_p.x + 50 > sweeper_p.x && 
				mine_p.y - 50 < sweeper_p.y && 
				mine_p.y + 50 > sweeper_p.y)
			{
				float distance = (mine_p - sweeper_p).distance();
				//cout << "distance: " << distance << endl;
				if (distance < HIT_DISTANCE)
				{
					mine.new_position();
					sweeper.get_brain().increase_fitness(1);
				}
				else if (distance < min_distance)
				{
					min_distance = distance;
					closest_mine = mine_p;
				}
			}	
		}
		if (sweeper.get_brain().get_fitness() > max_fitness)
		{
			max_fitness = sweeper.get_brain().get_fitness();
			for (Sweeper &sweeper2 : sweepers) sweeper2.set_best(false);
			sweeper.set_best(true);
		}
		sweeper.update(closest_mine);

		sweeper_p = sweeper.get();
		if (sweeper_p.x > SCREEN_WIDTH) sweeper_p.x = 0;
		else if (sweeper_p.x < 0) sweeper_p.x = SCREEN_WIDTH;
		if (sweeper_p.y > SCREEN_HEIGHT) sweeper_p.y = 0;
		else if (sweeper_p.y < 0) sweeper_p.y = SCREEN_HEIGHT;
		sweeper.set(sweeper_p);
	}
	ticks += 1;
	if (ticks > EPOCH_TICK_OVER)
	{
		ticks = 0;
		max_fitness = 0;
		vector<Brain> population = vector<Brain>();
		for (Sweeper sweeper : sweepers) population.push_back(sweeper.get_brain());
		population = Controller::epoch(population);
		for (int i = 0; i < sweepers.size(); i++) 
		{
			sweepers[i].set_brain(population[i]);
			sweepers[i].get_brain().set_fitness(0);
			sweepers[i].new_position();
		}
		for (Mine &mine : mines) mine.new_position();
	}
}

void Logic::draw(SDL_Renderer* renderer)
{
	for (Mine mine : mines) mine.draw(renderer);
	for (Sweeper sweeper : sweepers) sweeper.draw(renderer);
}
