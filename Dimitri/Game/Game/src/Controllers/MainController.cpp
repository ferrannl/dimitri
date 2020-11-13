#include "MainController.h"
using namespace Game;
Controllers::MainController::MainController()
{
	_window_controller = std::make_shared<WindowController>();
	_level_controller = std::make_shared<Controllers::LevelController>();
	_home_controller = std::make_shared<Controllers::HomeController>();
	_input_controller = std::make_shared<Controllers::InputController>();
}

void Game::Controllers::MainController::run()
{
	_input_controller->subscribe(this->shared_from_this());
	_input_controller->subscribe(_home_controller);
	_window_controller->create_window(1080, 720);
	_window_controller->set_level_textures(_level_controller->get_textures());
	_input_controller->poll_events();
}

void Controllers::MainController::update(const Events::InputEvent& object)
{
	switch (object.event_enum) {
	case Input::Enums::EventEnum::KEY_PRESS_C:
		if (!_window_controller->is_active("credits")) {
			_window_controller->clear_views();
			_window_controller->open_view("credits");
			_window_controller->open_view("fps");
			_level_controller->stop();
			_input_controller->unsubscribe(_level_controller);
		}
		break;
	case Input::Enums::EventEnum::KEY_PRESS_H:
		if (!_window_controller->is_active("help")) {
			_window_controller->clear_views();
			_window_controller->open_view("help");
			_window_controller->open_view("fps");
			_level_controller->stop();
			_input_controller->unsubscribe(_level_controller);
		}
		break;
	case Input::Enums::EventEnum::KEY_PRESS_L:
		if (!_window_controller->is_active("level")) {
			_window_controller->clear_views();
			_window_controller->open_view("level");
			_window_controller->open_view("fps");
			_input_controller->subscribe(_level_controller);
			_level_controller->start();
		}
		break;
	case Input::Enums::EventEnum::KEY_PRESS_ESC:
		if (!_window_controller->is_active("home")) {
			_window_controller->clear_views();
			_window_controller->open_view("home");
			_window_controller->open_view("fps");
			_level_controller->stop();
			_input_controller->unsubscribe(_level_controller);
		}
		break;
	case Input::Enums::EventEnum::KEY_PRESS_F:
		_window_controller->toggle_view_visibility("fps");
		break;
	case Input::Enums::EventEnum::KEY_PRESS_QUIT:
		exit(0);
	}
}
