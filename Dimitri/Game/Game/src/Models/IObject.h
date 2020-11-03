#pragma once
#include <vector>
#include <memory>
#include <string>
#include <src\Models\Texture.h>
#include <map>
#include <src\Helpers\BasePathHelper.h>
#include <src/Models/Sprite.h>
#include <src\Models\Shape.h>

namespace Game {
	namespace Models {
		class IObject {
		protected:
			/**
			*	Position object
			*/
			int _x;
			int _y;
			int _z;

			/**
			*	Size of object
			*/
			int _height;
			int _width;

			/**
			*	Object state ex: Walking, Climbing, Crouching, Jumping, Standing still. You could also specify a certain walking texture and change it every frame.
			*/
			std::string _state;

			/**
			*	Textures saved by state for easy access
			*/
			std::map<std::string, std::shared_ptr<Graphics::Models::Texture>> _textures;

			/**
			*	Shape of object
			*/
			std::shared_ptr<PhysicsCollision::Models::Shape> _shape;

			/**
			*	Initializes textures specific to object
			*/
			virtual void initialize_textures() = 0;

		public:
			IObject(int x, int y, int z, int height, int width);

			/**
			*	Returns texture based on state
			*/
			std::shared_ptr<Graphics::Models::Texture> get_texture();

			/**
			*	Returns all textures
			*/
			std::vector<std::shared_ptr<Graphics::Models::Texture>> get_all_textures();

			/**
			*	Returns x
			*/
			int get_x();

			/**
			*	Sets x
			*/
			void set_x(int value);

			/**
			*	Returns y
			*/
			int get_y();

			/**
			*	Sets x
			*/
			void set_y(int value);

			/**
			*	Returns z
			*/
			int get_z();

			/**
			*	Sets x
			*/
			void set_z(int value);

			/**
			*	Sets state
			*/
			void set_state(std::string value);

			/**
			*	Returns shape
			*/
			std::shared_ptr<PhysicsCollision::Models::Shape> get_shape();

			/**
			*	Sets shape
			*/
			void set_shape(std::shared_ptr<PhysicsCollision::Models::Shape> shape);

			/**
			*	Adds texture
			*/
			void add_texture(std::string state, std::shared_ptr<Graphics::Models::Texture> texture);

			/**
			*	Returns height
			*/
			int get_height();

			/**
			*	Returns width
			*/
			int get_width();

			/**
			*	Updates x/y values using shape
			*/
			void update();
		};
	}
}