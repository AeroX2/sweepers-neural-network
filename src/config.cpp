#include "config.hpp"

bool Config::read_from_file(string filename)
{
	ifstream file(filename);
	if (!file) return false;

	char param_description[25];
	file >> ROLLING_AVERAGE;  
	file >> param_description;  
	file >> TOURNAMENT;  
	file >> param_description;  
	file >> COMBINE_TWO_POINT;  
	file >> param_description;  
	file >> CONTROL_SWEEPER;  
	file >> param_description;  
	file >> POPULATION;  
	file >> param_description;  
	file >> MINE_LEN;  
	file >> param_description; 
	file >> EPOCH_TICK_OVER;  
	file >> param_description; 
	file >> HIT_DISTANCE;  
	file >> param_description; 
	file >> TOURNAMENT_SIZE;  
	file >> param_description; 
	file >> MUTATION_CHANCE;  
	file >> param_description; 
	file >> COMBINE_CHANCE;  
	file >> param_description; 
	file >> MAX_PERTURB;  
	file >> param_description; 
	file >> MAX_SWEEPER_TURN_RATE;  
	file >> param_description; 
	file >> BRAIN_HIDDEN_LEN;  
	file >> param_description; 

	cout << "Rolling_average: " << ROLLING_AVERAGE << endl;
	cout << "Tournament selection: " << TOURNAMENT << endl;
	cout << "Control sweeper: " << CONTROL_SWEEPER << endl;
	cout << "Combine Two Point: " << COMBINE_TWO_POINT << endl;
	cout << "Population: " << POPULATION << endl;
	cout << "Mine_len: " << MINE_LEN << endl;
	cout << "Epoch_tick_over: " << EPOCH_TICK_OVER << endl;
	cout << "Hit_distance: " << HIT_DISTANCE << endl;
	cout << "Tournament_size: " << TOURNAMENT_SIZE << endl;
	cout << "Mutation_chance: " << MUTATION_CHANCE << endl;
	cout << "Combine_chance: " << COMBINE_CHANCE << endl;
	cout << "Max_perturb: " << MAX_PERTURB << endl;
	cout << "Max_sweeper_turn_rate: " << MAX_SWEEPER_TURN_RATE << endl;
	cout << "Brain_hidden_len: " << BRAIN_HIDDEN_LEN << endl;

	return true;
}
