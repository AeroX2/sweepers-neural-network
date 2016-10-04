#include "plotter.hpp"

vector<vector<float>> Plotter::points;
vector<SDL_Color> Plotter::colors;

bool Plotter::dirty = true;
float Plotter::scale_x = 10;
float Plotter::scale_y = 30;
int Plotter::step_x = 0;
float Plotter::largest_y = 0;

void Plotter::init(float step_x)
{
	Plotter::step_x = step_x;
}

void Plotter::draw(SDL_Renderer* renderer)
{
	for (size_t id = 0; id < points.size(); id++) 
	{	
		int x = 0;
		for (size_t point = 0; point < points[id].size()-1; point++)
		{
			SDL_SetRenderDrawColor(renderer, colors[id].r, colors[id].g, colors[id].b, 255);
			int point_1 = round(SCREEN_HEIGHT - points[id][point] * scale_y);
			int point_2 = round(SCREEN_HEIGHT - points[id][point+1] * scale_y);
			SDL_RenderDrawLine(renderer, x * scale_x, point_1, (x + step_x) * scale_x, point_2);
			x += step_x;
		}
	}

	int y = round(SCREEN_HEIGHT - largest_y * scale_y);
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderDrawLine(renderer, 0, y, SCREEN_WIDTH, y);

	draw_font("Generation: " + to_string((int)points[0].size()-1), 10, 10);
	draw_font("Current max fitness: " + to_string((int)largest_y), 10, 30);

	dirty = false;
}

void Plotter::add_point(int id, float y)
{
	points[id].push_back(y);
	if (y * scale_y >= SCREEN_HEIGHT) scale_y /= 2;
	if (points[id].size() * step_x * scale_x >= SCREEN_WIDTH) scale_x /= 2;
	if (y > largest_y) largest_y = y;
	dirty = true;	
}

void Plotter::new_line(unsigned char r, unsigned char g, unsigned char b)
{
	vector<float> temp;
	temp.push_back(0);
	points.push_back(temp);
	SDL_Color temp2 = {r, g, b, 255};
	colors.push_back(temp2);
}

bool Plotter::is_dirty()
{
	return dirty;
}
