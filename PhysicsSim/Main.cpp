#include <stdio.h>
#include <SDL.h>
#include <utility>
#include "Physics.h"
#include <iostream>
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;

const int render_scale = 1;

void draw_circle(SDL_Renderer* renderer, std::pair<double, double> point, SDL_Color color)
{
	//SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	int x = point.first * render_scale;
	int y = point.second * render_scale;
	int radius = render_scale;
	for (int w = 0; w < radius * 2; w++)
	{
		for (int h = 0; h < radius * 2; h++)
		{
			int dx = radius - w;
			int dy = radius - h;
			if ((dx * dx + dy * dy) <= (radius * radius))
			{
				SDL_RenderDrawPoint(renderer, x + dx, y + dy);
			}
		}
	}
}

int main(int argc, char* args[]) {
	SDL_Event evnt;
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1366, 768, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	Physics* physics = new Physics();

	SDL_Rect simBorder;
	std::pair<int, int> simDimensions = physics->GetDimensions();
	simBorder.x = 0;
	simBorder.y = 0;
	simBorder.w = simDimensions.first * render_scale;
	simBorder.h = simDimensions.second * render_scale;
	int mouseX = 0;
	int mouseY = 0;
	auto lastTick = Clock::now();
	double elapsedSeconds = 0;
	bool running = { true };
	bool paused = { true };
	int c = 0;
	int maxVal = 255;
	while (running)
	{
		while (SDL_PollEvent(&evnt)) {
			switch (evnt.type) {
			case SDL_KEYDOWN:
				break;
			case SDL_KEYUP: paused = (evnt.key.keysym.sym == SDLK_SPACE) ? !paused : paused;
				break;
			case SDL_QUIT: running = false;
				break;
			default:
				break;
			}
		}
		bool mouseLeftDown = (SDL_GetMouseState(&mouseX, &mouseY) == SDL_BUTTON(1));
		physics->SetGrav(std::pair<double, double>(mouseX, mouseY), mouseLeftDown);

		auto currentTick = Clock::now();
		elapsedSeconds = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTick - lastTick).count() / static_cast<double>(1000000000);
		double fps = 1.0 / elapsedSeconds;
		double dt = 1.0 / fps;
		std::cout << "FPS: " << fps << "\n";
		lastTick = currentTick;

		//double temp = deltaTime / 1000.0;

		if (!paused)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

			physics->Update(dt);

			int n = physics->GetPoints();
			for (int i = 0; i < n; i++)
			{
				std::pair<double, double> point = physics->GetPoint(i);
				//SDL_Color color = physics->GetColorFor(i);
				//draw_circle(renderer, point, color);
				SDL_RenderDrawPoint(renderer, point.first, point.second);
			}
			SDL_RenderPresent(renderer);

			
		}
		//SDL_Delay(10);
	}
	SDL_Quit();
	return 0;
}
