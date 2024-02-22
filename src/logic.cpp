#include "logic.hpp"
#include "main.hpp"

Logic::Logic()
{
	ticks = 0;
	max_fitness = 0;
	control_sweeper = NULL;
	best_sweeper = NULL;
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
		new_mine.set_avoid(i >= AVOID_MINE_LEN);
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

		Mine closest_mine = *find_if(mines.begin(), mines.end(), [](Mine& m) { return !m.is_avoid(); } );
		Mine closest_avoid_mine = *find_if(mines.begin(), mines.end(), [](Mine& m) { return m.is_avoid(); } );

		Vector mine_p = closest_mine.get();
		Vector mine_avoid_p = closest_avoid_mine.get();

		float min_distance = (mine_p - sweeper_p).fake_distance();
		float min_avoid_distance = (mine_avoid_p - sweeper_p).fake_distance();

		for (Mine& mine : mines)
		{
			mine_p = mine.get();
			float distance = (mine_p - sweeper_p).fake_distance();
			/*if (mine_p.x - 50 < sweeper_p.x &&
				mine_p.x + 50 > sweeper_p.x &&
				mine_p.y - 50 < sweeper_p.y &&
				mine_p.y + 50 > sweeper_p.y)
			{*/
			//cout << "distance: " << distance << '\n';
			if (distance < HIT_DISTANCE*HIT_DISTANCE)
			{
				if (Main::is_interactive()) mine.set_dead(true);
				else
				{
				    while (true) {
                        mine.new_position();
                        mine_p = mine.get();

                        bool tooClose = false;
                        for (auto reference : sweepers)
                        {
                            Sweeper& sweeper = reference.get();
                            Vector& sweeper_p = sweeper.get();
                            float distance = (mine_p - sweeper_p).fake_distance();
                            if (distance < HIT_DISTANCE*HIT_DISTANCE*2) {
                                tooClose = true;
                                break;
                            }
                        }
                        if (!tooClose) break;
				    }
				}

				if (mine.is_avoid()) sweeper.get_fitness() *= PUNISHMENT;
				else sweeper.get_fitness() += REWARD;
			}
			else if (distance < min_distance && !mine.is_avoid())
			{
				min_distance = distance;
				closest_mine = mine;
			}

			distance = (mine_avoid_p - sweeper_p).fake_distance();
			if (distance < min_avoid_distance && mine.is_avoid())
			{
				min_avoid_distance = distance;
				closest_avoid_mine = mine;
			}
		}

		if (Main::is_interactive()) {
			mines.erase(remove_if(mines.begin(), mines.end(), [](auto mine){ return mine.is_dead(); }), mines.end());
		}

		//Control sweeper has a separate fitness to the brain
		if (sweeper.get_brain().get_fitness() > max_fitness)
		{
			max_fitness = sweeper.get_brain().get_fitness();
			for (size_t i = 0; i < sweepers.size()-CONTROL_SWEEPER; i++)
			{
				Sweeper& sweeper2 = sweepers[i].get();
				sweeper2.set_best(false);
			}
			sweeper.set_best(true);
			best_sweeper = &sweeper;
		}
		sweeper.update(closest_mine, closest_avoid_mine);

		sweeper_p = sweeper.get();
		Vector& sweeper_v = sweeper.get_vel();
		SDL_Rect r = sweeper.get_rect();

		if (sweeper_p.x > SCREEN_WIDTH-r.w/2)
		{
            sweeper_p.x = SCREEN_WIDTH-r.w/2;
            sweeper_v.x = 0;
            sweeper_v.y = 0;
		}
		else if (sweeper_p.x < r.w/2)
		{
            sweeper_p.x = r.w/2;
            sweeper_v.x = 0;
            sweeper_v.y = 0;
		}
		if (sweeper_p.y > SCREEN_HEIGHT-r.h/2)
		{
            sweeper_p.y = SCREEN_HEIGHT-r.h/2;
            sweeper_v.x = 0;
            sweeper_v.y = 0;
		}
		else if (sweeper_p.y < r.h/2)
		{
            sweeper_p.y = r.h/2;
            sweeper_v.x = 0;
            sweeper_v.y = 0;
		}
	}

	if (!Main::is_interactive() && ticks++ > EPOCH_TICK_OVER)
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

		if (CONTROL_SWEEPER)
		{
			control_sweeper->set_fitness(0);
			control_sweeper->new_position();
		}
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
	Main::draw_font("Epoch timer: " + to_string(ticks) + "/" + to_string(EPOCH_TICK_OVER), 10, 50);

	Main::draw_font("Press F to fast forward", 10, 70);
	Main::draw_font("Press B to see only the best", 10, 90);
	Main::draw_font("Press I to stop epoch to interact", 10, 110);
	Main::draw_font("Press C to clear the mines", 10, 130);
}

void Logic::clear_mines()
{
	mines.clear();
}

void Logic::mouse_down(int x, int y, bool avoid)
{
	Mine mine = Mine(x,y);
	mine.set_avoid(avoid);
	mines.push_back(mine);
}

