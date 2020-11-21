#pragma once
#include <memory>
#include <src\Controllers\WorldController.h>

/**
* \namespace Game
* \brief Namespace for the game
*/
namespace Game {
	/**
	* \namespace Game::Controllers
	* \brief Namespace for the controllers in the game
	*/
	namespace Controllers {
		/**
		*	Contains all code to interact with physics collision engine to simulate gravity and collision
		*/
		class PhysicsCollisionController {
		private:
			std::unique_ptr<PhysicsCollision::Controllers::WorldController> _world_controller;
		public:
			PhysicsCollisionController();

			/**
			*	Calls world_controller->simulate
			*/
			void simulate();

			/**
			*	Calls world_controller->destroy_bodies
			*/
			void destroy_shapes();

			/**
			*	Loads the shape into the world
			*/
			void load_shape(const std::shared_ptr<PhysicsCollision::Models::Shape>& _shape);

			/**
			*	Setup world
			*/
			void setup_world(int height, int width);

		};
	}
}
