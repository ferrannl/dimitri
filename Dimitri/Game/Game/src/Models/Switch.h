#pragma once
#include "IInteractable.h"

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
		* \class Switch
		* \brief Class contains the methods and data of the Switch
		*/
		class Switch : public Game::Models::IInteractable {
		private:
			int _switch_x;
		public:
			Switch(int x, int y, int z, int height, int width, Game::Enums::StateEnum state);

			/**
			* \brief Initializes Textures
			*/
			void initialize_textures();
			/**
			* \brief Updates the object when interacted with
			*/
			void interact(Controllers::LevelController* ctrl = NULL);
			void set_light(const int x);
		};
	}
}