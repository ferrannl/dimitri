#pragma once
#include "../Facades/ShapeFacade.h"
#include <iostream>
#include "../Enums/ShapeEnum.h"

#ifdef _WIN64
#ifdef PHYSICSCOLLISION_EXPORTS
#define PHYSICSCOLLISION_API __declspec(dllexport)
#else
#define PHYSICSCOLLISION_API __declspec(dllimport)
#endif
#else
#define PHYSICSCOLLISION_API
#endif
/**
* Namespace for the PhysicsCollision engine
*/
namespace PhysicsCollision {
	/**
	* Namespace for the Models
	*/
	namespace Models {
		/**
		* Shape model for creating shapes
		*/
		class PHYSICSCOLLISION_API Shape {
		private:
			/**
			* X position of a shape
			*/
			int _x;
			/**
			* Y position of a shape
			*/
			int _y;
			/**
			* Width of a shape
			*/
			int _width;
			/**
			* Height of a shape
			*/
			int _height;
			/**
			* Is dynamic boolean of a shape
			*/
			bool _is_dynamic;
			/**
			* Is interactable boolean of a shape
			*/
			bool _is_interactable;
		protected:
			/**
			* Shape type
			*/
			Enums::ShapeEnum _type;
			/**
			* Shape facade of a shape
			*/
			std::shared_ptr<Facades::ShapeFacade> _shape_facade;
		public:
			Shape(const int x, const int y, const int height, const int width, const bool is_dynamic, const bool is_interactable, const Enums::ShapeEnum type);
			/**
			* Returns the ShapeFacade from a shape
			*/
			std::shared_ptr<Facades::ShapeFacade> get_shape_facade()const;
			/**
			* Returns the type from a shape
			*/
			Enums::ShapeEnum get_type()const;
			/**
			* Sets the type of a shape
			*/
			void set_type(Enums::ShapeEnum type);
			/**
			*	Sets if a shape is interactable
			*/
			void set_is_interactable(bool is_interactable);
			/**
			* Sets the x position of a shape
			*/
			void set_x(float x);
			/**
			* Set the y position of a shape
			*/
			void set_y(float y);
			/**
			* Set the width of a shape
			*/
			void set_width(float width);
			/**
			* Set the height of a shape
			*/
			void set_height(float height);
			/**
			* Returns the x position of a shape
			*/
			float get_x()const;
			/**
			* Returns the y position of a shape
			*/
			float get_y()const;
			/**
			* Returns the width of a shape
			*/
			float get_width() const;
			/**
			* Returns the height of a shape
			*/
			float get_height() const;
			/**
			* Move the x position of a shape based on value. -1 or 1 means left or right
			*/
			void move_x(const int value)const;
			/**
			* Move the y position of a shape
			*/
			void move_y()const;
			/**
			* Returns the angle of a shape
			*/
			float get_angle()const;
			/**
			* Returns if a shape is dynamic
			*/
			bool get_is_dynamic() const;
			/**
			* Returns if a shape is interactable
			*/
			bool get_is_interactable() const;
			/**
			* Sets the dynamic property of a shape
			*/
			void set_is_dynamic(bool is_dynamic);
			/**
			* Returns true when there is collision between two shapes. Else returns false
			*/
			bool check_collision(std::shared_ptr<Models::Shape> shape);
			
			/**
			* Returns true when there is collision between the bottom of current shape en the top of the other shape. Else returns false
			*/
			bool check_bottom_collision(std::shared_ptr<Models::Shape> shape);
		};
	}
}
