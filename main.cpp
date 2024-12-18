#include <iostream>
#include <SDL.h>

#include <ctime>

constexpr int SCREEN_WIDTH=800;
constexpr int SCREEN_HEIGHT=600;


namespace {

void render(SDL_Window* window) {
	SDL_Surface* surface = SDL_GetWindowSurface(window);
	SDL_FillRect(surface, nullptr, SDL_MapRGB( surface->format, 0, 0, 55));

	SDL_UpdateWindowSurface(window);
}

void loop(SDL_Window* window) {
	bool running = true;
	int frames = 0;
	int total_frames = 0;

	const int64_t start_ticks = SDL_GetTicks64();
	int64_t last_second = start_ticks;

	while (running) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}

			if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym){
				case SDLK_q:
				case SDLK_ESCAPE:
					running = false;
					break;
				default:
					break;
				}
			}
		}

		render(window);


		// Performance measurements.
		frames++;
		total_frames++;

		const int64_t now_ticks = SDL_GetTicks64();
		if ((now_ticks - last_second) > 1000) {
			std::cout << "FPS: " << frames <<  "[avg: " << static_cast<float>(total_frames) / (now_ticks - start_ticks) * 1000  << "   total: " << total_frames << ", time: " << static_cast<float>(now_ticks - start_ticks) << "s]" << std::endl;
			frames = 0;
			last_second = now_ticks;
		}

	}
}

}  // namespace

int main(int argc, const char** argv) {

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cerr << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
		return -1;
	}

	SDL_Window* window = SDL_CreateWindow("Hello Boomer!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if (window == nullptr) {
		std::cerr << "Error creating SDL window: " << SDL_GetError() << std::endl;
		return -2;
	}

	loop(window);

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}