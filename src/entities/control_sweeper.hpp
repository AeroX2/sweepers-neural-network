#ifndef CONTROL_SWEEPER_H
#define CONTROL_SWEEPER_H

#include "sweeper.hpp"

class Control_Sweeper : public Sweeper
{
	public:
		static Control_Sweeper* create(Vector p, Brain& brain);
		void update(Mine mine) override;

		float& get_fitness() override;
		void set_fitness(float fitness) override;
	private:
		Control_Sweeper(Vector p, Brain& brain);
		float fitness;
};

#endif
