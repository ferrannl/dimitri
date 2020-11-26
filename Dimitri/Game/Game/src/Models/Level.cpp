#include "Level.h"
using namespace Game;

Models::Level::Level(const std::shared_ptr<Controllers::AudioController> audio_controller) : _audio_controller(audio_controller)
{
	_physics_collision_controller = std::make_shared<Game::Controllers::PhysicsCollisionController>();
	_timer = std::make_shared<Models::Timer>();
	_interactables = {};
	_lights = {};
	_players = {};
	_shapes = {};
	_tiles = {};
}

void Models::Level::add_music(std::string audio_name, std::string path)
{
	_audio_controller->add_music(audio_name, path);
}

void Game::Models::Level::add_sound(std::string audio_name, std::string path)
{
	_audio_controller->add_sound(audio_name, path);
}

void Models::Level::play_music(std::string audio_name)
{
	_audio_controller->play_audio(audio_name);
}

void Game::Models::Level::start_timer()
{
	_timer->start();
}

std::shared_ptr<Models::Timer> Game::Models::Level::get_timer()
{
	return _timer;
}

void Models::Level::stop_music(std::string audio_name)
{
	_audio_controller->stop_audio(audio_name);
}

void Game::Models::Level::pause_music(std::string audio_name)
{
	_audio_controller->pause_audio(audio_name);
}

void Game::Models::Level::resume_music(std::string audio_name)
{
	_audio_controller->resume_audio(audio_name);
}


void Game::Models::Level::load_objects()
{
	//Here a file is loaded/parsed and turned into a level
	_height = 2000;
	_width = 4000;

	_physics_collision_controller->setup_world(_height, _width);

	_player = std::make_shared<Player>(200, 200, 1, 50, 50, Game::Enums::StateEnum::RIGHT);
	_players.push_back(_player);

	//floor
	_tiles.push_back(std::make_shared<Wall>(0, 0, 1, 25, 25, Game::Enums::StateEnum::LEFT));

	_tiles.push_back(std::make_shared<Wall>(25, 0, 1, 25, 1870, Game::Enums::StateEnum::HORIZONTAL));

	_tiles.push_back(std::make_shared<Wall>(1895, 0, 1, 25, 25, Game::Enums::StateEnum::RIGHT));

	//background
	_background = std::make_shared<Graphics::Models::Sprite>(0, 0, 0, _height, _width, 0,Utility::Helpers::get_base_path() + std::string{ "/assets/images/bg.png" }, Graphics::Enums::FlipEnum::HORIZONTAL, true);


	//platform 1
	_tiles.push_back(std::make_shared<Wall>(200, 150, 1, 25, 25, Game::Enums::StateEnum::LEFT));

	_tiles.push_back(std::make_shared<Wall>(225, 150, 1, 25, 100, Game::Enums::StateEnum::HORIZONTAL));

	_tiles.push_back(std::make_shared<Wall>(325, 150, 1, 25, 25, Game::Enums::StateEnum::RIGHT));

	//platform 2
	_tiles.push_back(std::make_shared<Wall>(400, 300, 1, 25, 25, Game::Enums::StateEnum::LEFT));

	_tiles.push_back(std::make_shared<Wall>(425, 300, 1, 25, 100, Game::Enums::StateEnum::HORIZONTAL));

	_tiles.push_back(std::make_shared<Wall>(525, 300, 1, 25, 25, Game::Enums::StateEnum::RIGHT));

	//platform 3
	_tiles.push_back(std::make_shared<Wall>(600, 450, 1, 25, 25, Game::Enums::StateEnum::LEFT));

	_tiles.push_back(std::make_shared<Wall>(625, 450, 1, 25, 100, Game::Enums::StateEnum::HORIZONTAL));

	_tiles.push_back(std::make_shared<Wall>(725, 450, 1, 25, 25, Game::Enums::StateEnum::RIGHT));

	//interactables
	_interactables.push_back(std::make_shared<Switch>(650, 475, 2, 25, 25, Game::Enums::StateEnum::LEFT));

	//miscelanious
	_lights.push_back(std::make_shared<LightBeam>(700, 25, 0, 300, 300, Game::Enums::StateEnum::HORIZONTAL));

	_tiles.push_back(std::make_shared<Lamp>(800, 300, 0, 100, 100, Game::Enums::StateEnum::HORIZONTAL));

	//border
	_shapes.push_back(std::make_shared<PhysicsCollision::Models::Shape>(0, _height, 1, _width, false, false , PhysicsCollision::Enums::ShapeEnum::Square));//top
	_shapes.push_back(std::make_shared<PhysicsCollision::Models::Shape>(0, -1, 1, _width, false, false, PhysicsCollision::Enums::ShapeEnum::Square));//bot
	_shapes.push_back(std::make_shared<PhysicsCollision::Models::Shape>(-1, 0, _height, 1, false, false, PhysicsCollision::Enums::ShapeEnum::Square));//lef
	_shapes.push_back(std::make_shared<PhysicsCollision::Models::Shape>(_width, 0, _height, 1, false, false, PhysicsCollision::Enums::ShapeEnum::Square));//rig

	add_shapes();
}

void Game::Models::Level::add_shapes()
{
	for(std::shared_ptr<Game::Models::IObject> _player : _players)
	{
		_physics_collision_controller->load_shape(_player.get()->get_shape());
	}
	for (std::shared_ptr<Game::Models::IObject> tile : _tiles)
	{
		_physics_collision_controller->load_shape(tile.get()->get_shape());
	}
	for (std::shared_ptr<Game::Models::IInteractable> interactable : _interactables)
	{
		_physics_collision_controller->load_shape(interactable.get()->get_shape());
	}
	for (std::shared_ptr<PhysicsCollision::Models::Shape> shape : _shapes)
	{
		_physics_collision_controller->load_shape(shape);
	}
	for (std::shared_ptr<Game::Models::IObject> light : _lights)
	{
		_physics_collision_controller->load_shape(light.get()->get_shape());
	}
}

std::vector<std::shared_ptr<Graphics::Models::Texture>> Game::Models::Level::get_textures() const
{
	std::vector<std::shared_ptr<Graphics::Models::Texture>> textures = {};
	std::vector<std::shared_ptr<Graphics::Models::Texture>> temp = _player->get_all_textures();
	textures.insert(textures.end(), temp.begin(), temp.end());
	textures.push_back(_background);
	for (std::shared_ptr<IObject> tile : _tiles)
	{
		temp = tile->get_all_textures();
		textures.insert(textures.end(), temp.begin(), temp.end());
	}
	for (std::shared_ptr<IObject> light : _lights)
	{
		temp = light->get_all_textures();
		textures.insert(textures.end(), temp.begin(), temp.end());
	}
	for (std::shared_ptr<IObject> interactable : _interactables)
	{
		temp = interactable->get_all_textures();
		textures.insert(textures.end(), temp.begin(), temp.end());
	}
	return textures;
}

std::vector<std::shared_ptr<Game::Models::IObject>> Game::Models::Level::get_lights() const
{
	return _lights;
}

std::shared_ptr<Game::Models::Player> Game::Models::Level::get_player() const
{
	return _player;
}

std::vector<std::shared_ptr<Game::Models::IObject>> Game::Models::Level::get_tiles() const
{
	return _tiles;
}

std::vector<std::shared_ptr<Game::Models::IInteractable>> Game::Models::Level::get_interactables() const
{
	return _interactables;
}

std::shared_ptr<Game::Controllers::PhysicsCollisionController> Game::Models::Level::get_physics_collision_controller() const
{
	return _physics_collision_controller;
}

void Game::Models::Level::simulate()
{
	_physics_collision_controller->simulate();
}

int Game::Models::Level::get_level_height() const
{
	return _height;
}

int Game::Models::Level::get_level_width() const
{
	return _width;
}
