#include "Wall.h"

Game::Models::Wall::Wall(int x, int y, int z, int height, int width) : Game::Models::IObject(x, y, z, height, width)
{
	initialize_textures();
}

void Game::Models::Wall::initialize_textures()
{
	_state = "horizontal";
	add_texture("horizontal", std::make_shared<Graphics::Models::Sprite>(0, 0, 1, 75, 75, 0, Utility::Helpers::get_base_path() + std::string{ "/assets/images/ground.png" }, Graphics::Enums::FlipEnum::NONE));
	add_texture("vertical", std::make_shared<Graphics::Models::Sprite>(0, 0, 1, 75, 75, 0, Utility::Helpers::get_base_path() + std::string{ "/assets/images/ground.png" }, Graphics::Enums::FlipEnum::VERTICAL));
	add_texture("right", std::make_shared<Graphics::Models::Sprite>(0, 0, 1, 75, 75, 0, Utility::Helpers::get_base_path() + std::string{ "/assets/images/ground_end.png" }, Graphics::Enums::FlipEnum::NONE));
	add_texture("left", std::make_shared<Graphics::Models::Sprite>(0, 0, 1, 75, 75, 0, Utility::Helpers::get_base_path() + std::string{ "/assets/images/ground_end.png" }, Graphics::Enums::FlipEnum::HORIZONTAL));
}
