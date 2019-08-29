#pragma once

#include "..\\engine\system.h"
#include "..\\external\SDL2-2.0.10\include\SDL.h"
#include "..\\external\SDL2-2.0.10\include\SDL_image.h"
#include "..\\external\SDL2-2.0.10\include\SDL_ttf.h"

#include <string>

class Renderer : public System {
public:
	Renderer(Engine* engine) : System(engine) {}
	~Renderer() {}

	bool Startup() override;
	void Update() override;
	void Shutdown() override;

	void Create(const std::string& name, int width, int height);
	void BeginFrame();
	void EndFrame();

	SDL_Renderer* GetSDLRenderer() { return renderer_; }

	float GetAspectRatio() { return screen_width_ / static_cast<float>(screen_height_); }

private:
	SDL_Window* window_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;

	int screen_width_;
	int screen_height_;
};