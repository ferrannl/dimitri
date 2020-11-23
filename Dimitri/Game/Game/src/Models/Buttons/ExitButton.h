#pragma once
#include "../Button.h"
#include <cstdlib>

/**
* \namespace Game
* \brief Namespace for the game
*/
namespace Game {
	/**
	* \namespace Game::Models
	* \brief Namespace for the models in the game
	*/
	namespace Models {
		/**
		* \namespace Game::Buttons
		* \brief Namespace for the buttons in the game
		*/
		namespace Buttons {
			/**
			* \class ExitButton
			* \brief Class contains the methods close the game
			*/
			class ExitButton : public Game::Models::Button {
			private:
			public:
				ExitButton(int x, int y, int z, int height, int width, Game::Enums::StateEnum state, int scene_height, Graphics::Models::Center center);

				/**
				* \brief Updates the object when interacted with
				*/
				void interact(Controllers::LevelController* ctrl = NULL);
			};
		}
	}
}