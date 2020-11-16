#include "HomeController.h"
using namespace Game;

void Game::Controllers::HomeController::init_buttons()
{
	_buttons.push_back(std::make_shared<Game::Models::Button>(_scene_width / 2 - 35, (_scene_height / 4 * 3) - 150, 1, 50, 70, Game::Enums::StateEnum::RIGHT));
	_buttons.push_back(std::make_shared<Game::Models::Button>(_scene_width / 2 - 35, (_scene_height / 4 * 3) - 225, 1, 50, 70, Game::Enums::StateEnum::RIGHT));
}

Game::Controllers::HomeController::HomeController(int sceneheight, int scenewidth)
{
	_scene_height = sceneheight;
	_scene_width = scenewidth;
	init_buttons();
}

void Game::Controllers::HomeController::update(const Game::Events::InputEvent& object)
{
	switch (object.event_enum) {
	case Input::Enums::EventEnum::MOUSE_PRESSED_LEFT:
		int x = std::get<0>(object.mouse_pos);
		int y = std::get<1>(object.mouse_pos);
		for (auto& b : _buttons)
			if (b->get_x() < x)
				if (x < b->get_x() + b->get_width())
					if (b->get_y() > y)
						if (y < b->get_y() + b->get_height())
						{
							std::cout << "clicked on: " + x + y << std::endl;
						}
		break;
	}
}

std::vector<std::shared_ptr<Graphics::Models::Texture>> Game::Controllers::HomeController::get_textures() const
{
	std::vector<std::shared_ptr<Graphics::Models::Texture>> button_textures;
	for (auto& b : _buttons) {
		button_textures.push_back(b->get_texture());
	}
	return button_textures;
}