#pragma once
#include <sdl.h> 
#include "../Models/Sprite.h"
#include <iostream>
#include "TextureFacade.h"
#include <vector>
#include "../Adapters/FlipEnumAdapter.h"

namespace Facades {
	class __declspec(dllexport) WindowFacade {
	private:
		std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> _window;
		std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> _renderer;
		Adapters::FlipEnumAdapter _flip_enum_adapter;

		std::shared_ptr<Facades::TextureFacade> get_if_exists(std::shared_ptr<std::vector<std::unique_ptr<Models::Sprite>>> sprites, const std::string path);
	public:
		WindowFacade();

		void create_renderer();
		void create_window(const std::string title, const int height, const int width);
		void create_sprites(std::shared_ptr<std::vector<std::unique_ptr<Models::Sprite>>> sprites);
		void destroy();
		void update_window(std::shared_ptr<std::vector<std::unique_ptr<Models::Sprite>>> sprites);
	};
}