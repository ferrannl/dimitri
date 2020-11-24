#pragma once
#include "../Abstract/Object.h"

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
		* \class Lamp
		* \brief Class contains the data of the Lamp
		*/
		class Camera : public Models::Object {
		public:
			Camera(int x, int y, int z, int height, int width, Enums::DirectionEnum state, Graphics::Models::Center center);

			/**
			* \brief Initializes Textures
			*/
			void initialize_textures();
		};
	}
}