#include "CommandMediator.h"

namespace Game {
	namespace Mediators {
		std::unique_ptr<CommandMediator> CommandMediator::_instance{ nullptr };

		CommandMediator::CommandMediator(const std::shared_ptr<Controllers::MainController> main_controller) :
			_factory{ std::make_unique<Commands::CommandFactory>(main_controller) } { }

		CommandMediator* CommandMediator::instance()
		{
			if (_instance.get() == nullptr) throw "CommandMediator is not initialized";
			return _instance.get();
		}

		void CommandMediator::init(const std::shared_ptr<Controllers::MainController> main_controller)
		{
			_instance.reset(new CommandMediator(main_controller));
		}

		void CommandMediator::notify(const BaseComponent& sender, Events::InputEvent event)
		{
			if (sender.get_identifier() == "MainController") {
				switch (event.event_enum) {
				case Input::Enums::EventEnum::KEY_PRESS_QUIT:
					_factory->get_command(Enums::CommandEnum::EXIT_GAME)->execute();
					break;
				case Input::Enums::EventEnum::KEY_PRESS_F:
					_factory->get_command(Enums::CommandEnum::TOGGLE_FPS_VIEW)->execute();
					break;
				}
			}
			else if (sender.get_identifier() == "LevelController") {
				BaseComponent& not_const = const_cast<BaseComponent&>(sender);
				auto& ctrl = dynamic_cast<Controllers::LevelController&>(not_const);
				switch (ctrl.get_state()) {
				case Enums::LevelStateEnum::PAUSED:
					switch (event.event_enum) {
					case Input::Enums::EventEnum::MOUSE_PRESSED_LEFT:
						notify_buttons(sender, event, {
							{Enums::ButtonEnum::PAUSED_START, Enums::CommandEnum::PAUSE_LEVEL},
							{Enums::ButtonEnum::PAUSED_HOME, Enums::CommandEnum::OPEN_HOME_VIEW}
							});
						break;
					case Input::Enums::EventEnum::KEY_PRESS_P:
						_factory->get_command(Enums::CommandEnum::PAUSE_LEVEL)->execute();
						break;
					}
					break;
				case Enums::LevelStateEnum::GAME_OVER:
					switch (event.event_enum) {
					case Input::Enums::EventEnum::MOUSE_PRESSED_LEFT:
						notify_buttons(sender, event, {
							{Enums::ButtonEnum::GAMEOVER_START, Enums::CommandEnum::LOAD_LEVEL},
							{Enums::ButtonEnum::GAMEOVER_HOME, Enums::CommandEnum::OPEN_HOME_VIEW}
							});
						break;
					}
					break;
				case Enums::LevelStateEnum::WIN:
					switch (event.event_enum) {
					case Input::Enums::EventEnum::MOUSE_PRESSED_LEFT:
						notify_buttons(sender, event, { {Enums::ButtonEnum::WIN_HOME, Enums::CommandEnum::OPEN_HOME_VIEW} });
						break;
					}
					break;
				default:
					switch (event.event_enum) {
					case Input::Enums::EventEnum::KEY_PRESS_LEFT:
						_factory->get_command(Enums::CommandEnum::PLAYER_MOVE_LEFT)->execute();
						break;
					case Input::Enums::EventEnum::KEY_PRESS_RIGHT:
						_factory->get_command(Enums::CommandEnum::PLAYER_MOVE_RIGHT)->execute();
						break;
					case Input::Enums::EventEnum::KEY_PRESS_UP:
						_factory->get_command(Enums::CommandEnum::PLAYER_JUMP)->execute();
						break;
					case Input::Enums::EventEnum::KEY_PRESS_E:
						_factory->get_command(Enums::CommandEnum::PLAYER_INTERACT)->execute();
						break;
					case Input::Enums::EventEnum::KEY_PRESS_P:
						_factory->get_command(Enums::CommandEnum::PAUSE_LEVEL)->execute();
						break;
					}
					break;
				}
			}
			else if (sender.get_identifier() == "HomeController") {
				switch (event.event_enum) {
				case Input::Enums::EventEnum::MOUSE_PRESSED_LEFT:
					notify_buttons(sender, event, {
						{Enums::ButtonEnum::START, Enums::CommandEnum::LOAD_LEVEL},
						{Enums::ButtonEnum::HELP, Enums::CommandEnum::OPEN_HELP_VIEW},
						{Enums::ButtonEnum::CREDITS, Enums::CommandEnum::OPEN_CREDITS_VIEW},
						{Enums::ButtonEnum::EXIT, Enums::CommandEnum::EXIT_GAME},
						{Enums::ButtonEnum::HIGHSCORE, Enums::CommandEnum::LOAD_HIGHSCORE},
						});
					break;
				}
			}
			else if (sender.get_identifier() == "CreditsController")
			{
				switch (event.event_enum) {
				case Input::Enums::EventEnum::MOUSE_PRESSED_LEFT:
					notify_buttons(sender, event, { {Enums::ButtonEnum::HOME, Enums::CommandEnum::OPEN_HOME_VIEW} });
					break;
				}
			}
			else if (sender.get_identifier() == "HelpController")
			{
				switch (event.event_enum) {
				case Input::Enums::EventEnum::MOUSE_PRESSED_LEFT:
					notify_buttons(sender, event, { {Enums::ButtonEnum::HOME, Enums::CommandEnum::OPEN_HOME_VIEW} });
					break;
				}
			}
			else if (sender.get_identifier() == "IncreaseGameSpeedButton") {
				switch (event.event_enum) {
				case Input::Enums::EventEnum::KEY_PRESS_LEFT:
					_factory->get_command("increase_game_speed")->execute();
					break;
				}
			}
			else if (sender.get_identifier() == "DecreaseGameSpeedButton") {
				switch (event.event_enum) {
				case Input::Enums::EventEnum::KEY_PRESS_LEFT:
					_factory->get_command("decrease_game_speed")->execute();
					break;
				}
			}
			else if (sender.get_identifier() == "HighscoreButton") {
				switch (event.event_enum) {
				case Input::Enums::EventEnum::KEY_PRESS_LEFT:
					_factory->get_command("load_highscore")->execute();
				}
			}
				else if (sender.get_identifier() == "HighscoreManager")
				{
					switch (event.event_enum) {
					case Input::Enums::EventEnum::MOUSE_PRESSED_LEFT:
						notify_buttons(sender, event, { {Enums::ButtonEnum::HOME, Enums::CommandEnum::OPEN_HOME_VIEW} });
						break;
				}
			}
		}

		void CommandMediator::notify(const BaseComponent& sender, Enums::LevelStateEnum event)
		{
			if (sender.get_identifier() == "LevelController") {
				switch (event) {
				case Enums::LevelStateEnum::ACTIVE:
					_factory->get_command(Enums::CommandEnum::OPEN_LEVEL_VIEW)->execute();
					break;
				case Enums::LevelStateEnum::WIN:
					_factory->get_command(Enums::CommandEnum::OPEN_WIN_LEVEL_VIEW)->execute();
					break;
				case Enums::LevelStateEnum::GAME_OVER:
					_factory->get_command(Enums::CommandEnum::OPEN_GAME_OVER_LEVEL_VIEW)->execute();
					break;
				case Enums::LevelStateEnum::PAUSED:
					_factory->get_command(Enums::CommandEnum::OPEN_PAUSE_LEVEL_VIEW)->execute();
					break;
				}
			}
		}

		void CommandMediator::notify_buttons(const BaseComponent& sender, Events::InputEvent event, const std::map<Enums::ButtonEnum, Enums::CommandEnum>& button_command)
		{
			for (auto& b : sender.get_buttons()) {
				if (b->is_clicked(event)) {
					for (auto& c : button_command) {
						if (b->get_identifier() == c.first) {
							_factory->get_command(c.second)->execute();
						}
					}
				}
			}
		}
	}
}
