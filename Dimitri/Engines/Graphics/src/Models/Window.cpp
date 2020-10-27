#include "Window.h"
using namespace Graphics;

Models::Window::Window(const std::string title, const int height, const int width) : _title{ title }, _height{ height }, _width{ width } {
	_facade = std::make_unique<Facades::WindowFacade>();
}

std::shared_ptr<Models::Texture> Models::Window::get_matching_texture(const std::shared_ptr<Models::Texture>& texture) const
{
	for (std::shared_ptr<Models::Texture> t : _textures) {
		if (t.get()->matches(texture)) {
			return t;
		}
	}
	return nullptr;
}

int Models::Window::create()
{
	int retVal = NULL;

	retVal = _facade->create_window(_title, _height, _width);
	retVal = _facade->create_renderer();

	return retVal;
}

void Models::Window::update()
{
	_facade->update_window(_textures);
}

void Models::Window::destroy()
{
	_facade->destroy();
}

void Graphics::Models::Window::add_texture(const std::shared_ptr<Texture>& texture)
{
	_textures.push_back(texture);
	_facade->create_texture(texture, get_matching_texture(texture));
}

void Graphics::Models::Window::remove_texture(const std::shared_ptr<Texture>& texture)
{
	auto it = std::find(_textures.begin(), _textures.end(), texture);

	// If element was found 
	if (it != _textures.end()) {
		int index = std::distance(_textures.begin(), it);
		_textures.erase(_textures.begin() + index);
	}
}

std::vector<std::shared_ptr<Models::Texture>> Graphics::Models::Window::get_textures() const
{
	return _textures;
}

int Models::Window::get_height() const
{
	return _height;
}

int Models::Window::get_width() const
{
	return _width;
}

const std::string Models::Window::get_title() const
{
	return _title;
}