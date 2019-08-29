#include "renderer.h"

bool Renderer::Startup() {
	bool start_success = true;

	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

	TTF_Init();

	return start_success;
}

void Renderer::Update() {}

void Renderer::Shutdown() {
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);

	IMG_Quit();

	TTF_Quit();
}

void Renderer::Create(const std::string& name, int width, int height) {
	window_ = SDL_CreateWindow(name.c_str(), 30, 30, width, height, 0);
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	screen_width_ = width;
	screen_height_ = height;
}

void Renderer::BeginFrame() {
	SDL_RenderClear(renderer_);
}

void Renderer::EndFrame() {
	SDL_RenderPresent(renderer_);
}
