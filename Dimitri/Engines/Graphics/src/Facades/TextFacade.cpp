#include "TextFacade.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

Graphics::Facades::TextFacade::TextFacade(const std::string& path, const std::string& text, const Graphics::Models::Color& color, const int height, int opacity) :
	TextureFacade(path, opacity), _text{ text }, _color{ color.red, color.green, color.blue }, _height{ height } {}

void Graphics::Facades::TextFacade::create_texture(std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>& renderer)
{
	try {
		//Open the font
		TTF_Font* gFont = TTF_OpenFont(_path.c_str(), _height * 2);
		if (gFont == NULL)
		{
			throw Exceptions::CannotLoadFont();
		}

		//Render text surface
		SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, _text.c_str(), _color);
		if (textSurface == NULL)
		{
			SDL_FreeSurface(textSurface);
			throw Exceptions::CannotLoadImage();
		}

		//Create texture from surface pixels
		SDL_Texture* t = SDL_CreateTextureFromSurface(renderer.get(), textSurface);
		SDL_SetTextureBlendMode(t, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(t, _opacity);
		_texture.reset(t);
		if (_texture == NULL)
		{
			throw Exceptions::CannotCreateTexture();
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
	catch (Exceptions::TTFInitFailed& e) {
		std::cout << e.get() << std::endl;
	}
	catch (Exceptions::CannotLoadImage& e) {
		std::cout << e.get() << ": " << _path << std::endl;
	}
	catch (Exceptions::CannotCreateTexture& e) {
		std::cout << e.get();
	}
}
