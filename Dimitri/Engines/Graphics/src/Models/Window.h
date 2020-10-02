#pragma once
#include <SDL.h>
#include <string>
#include "../Facades/WindowFacade.h"
#include <vector>

namespace Models {
	class __declspec(dllexport) Window
	{
	private:
		int _x;
		int _y;
		int _height;
		int _width;
		const char* _title;
		Facades::WindowFacade* _facade;
		std::vector<Sprite*> _sprites;

	public:
		Window(const char* title, const int x, const int y, const int height, const int width)
			: _x{ x }, _y{ y }, _height{ height }, _width{ width }, _title{ title } {
			_facade = new Facades::WindowFacade();
		}

		void create_sprites();
		void create();
		void update();
		void destroy();
		void set_sprites(const std::vector<Models::Sprite*> sprites);
		const std::vector<Models::Sprite*> get_sprites();
		const int get_x();
		const int get_y();
		const int get_height();
		const int get_width();
		const char* get_title();
	};
}