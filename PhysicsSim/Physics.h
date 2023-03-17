#include <utility>
#include <SDL.h>

#pragma once
class Physics
{
public:
	Physics();
	~Physics();
	void SetGrav(std::pair<double, double> gravPos, bool isEnabled);
	void Update(double dTime);
	std::pair<int, int> GetDimensions();
	int GetPoints();
	//SDL_Color GetColorFor(int index);
	std::pair<double, double> GetPoint(int index);

};