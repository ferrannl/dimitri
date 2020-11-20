#include "LevelController.h"
using namespace Game;

Game::Controllers::LevelController::LevelController()
{
	_level = std::make_shared<Game::Models::Level>();
	_level->load_objects();
	_level->add_music("level1", "/assets/audio/billy.wav");
	_state = Enums::LevelStateEnum::INACTIVE;
}

std::vector<std::shared_ptr<Graphics::Models::Texture>> Game::Controllers::LevelController::get_textures() const
{
	return _level->get_textures();
}

void Game::Controllers::LevelController::update(const Game::Events::InputEvent& object)
{
	switch (object.event_enum) {
	case Input::Enums::EventEnum::KEY_PRESS_LEFT:
		if (_state == Enums::LevelStateEnum::ACTIVE) {
			_level->get_player()->set_state(Game::Enums::StateEnum::LEFT);
			_level->get_player()->get_shape()->move_x(-1);
		}
		break;
	case Input::Enums::EventEnum::KEY_PRESS_RIGHT:
		if (_state == Enums::LevelStateEnum::ACTIVE) {
			_level->get_player()->set_state(Game::Enums::StateEnum::RIGHT);
			_level->get_player()->get_shape()->move_x(1);
		}
		break;
	case Input::Enums::EventEnum::KEY_PRESS_UP:
		if (_state == Enums::LevelStateEnum::ACTIVE) {
			_level->get_player()->get_shape()->move_y();
		}
		break;
	case Input::Enums::EventEnum::KEY_PRESS_E:
		if (_state == Enums::LevelStateEnum::ACTIVE) {
			for (std::shared_ptr<Models::IInteractable> interactable : _level->get_interactables())
			{
				if (_level->get_player()->get_shape()->check_collision(interactable->get_shape()))
				{
					interactable->interact();
				}
			}
		}
		break;
	case Input::Enums::EventEnum::KEY_PRESS_P:
		if (_state == Enums::LevelStateEnum::ACTIVE) {
			set_state(Enums::LevelStateEnum::PAUSED);
		}
		else if (_state == Enums::LevelStateEnum::PAUSED) {
			start();
		}
		break;
	case Input::Enums::EventEnum::KEY_PRESS_W:
		// this will obviously be triggered by an event in the future, for now a hardcoded key
		set_state(Enums::LevelStateEnum::WIN);
		break;
	case Input::Enums::EventEnum::KEY_PRESS_G:
		// this will obviously be triggered by an event in the future, for now a hardcoded key
		set_state(Enums::LevelStateEnum::GAME_OVER);
	}
}

std::shared_ptr<Game::Models::Level> Game::Controllers::LevelController::get_level() const
{
	return _level;
}

void Game::Controllers::LevelController::start()
{
	set_state(Enums::LevelStateEnum::ACTIVE);
}

void Game::Controllers::LevelController::stop()
{
	set_state(Enums::LevelStateEnum::INACTIVE);
}

void Game::Controllers::LevelController::set_state(Enums::LevelStateEnum new_state)
{
	if (new_state != _state) {
		auto old_state = _state;
		_state = new_state;

		if (old_state == Enums::LevelStateEnum::ACTIVE) {
			// active -> pause/win/game_over/inactive
			_simulation_thread.join();
			_level->stop_music("level1");
		}
		else if (new_state == Enums::LevelStateEnum::ACTIVE) {
			// pause/win/game_over/inactive -> active
			_simulation_thread = std::thread(&Game::Controllers::LevelController::simulate, this);
			_level->play_music("level1");
		}
		notify(_state);
	}
}

void  Game::Controllers::LevelController::simulate() {
	while (_state == Enums::LevelStateEnum::ACTIVE) {
		sleep_for(1ms);
		_level->simulate();
		_level->get_player()->update();
	}
}

void Game::Controllers::LevelController::notify(const Enums::LevelStateEnum& object) {
	for (auto observer : _observers) {
		observer->update(object);
	}
}

void Game::Controllers::LevelController::subscribe(const std::shared_ptr<Utility::Interfaces::IObserver<Enums::LevelStateEnum>>& observer) {
	_observers.push_back(observer);
}

void Game::Controllers::LevelController::unsubscribe(const std::shared_ptr<Utility::Interfaces::IObserver<Enums::LevelStateEnum>>& observer)
{
	_observers.erase(std::remove(_observers.begin(), _observers.end(), observer), _observers.end());
}