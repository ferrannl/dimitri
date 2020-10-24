#include "MouseFacade.h"
#include <SDL.h>
#include <SDL_mouse.h>

std::tuple<int, int> Facades::MouseFacade::get_mouse_position() const
{
	int x, y;
	SDL_GetGlobalMouseState(&x, &y);
	return std::tuple<int, int>{x, y};
}