#pragma once
#include "../Facades/ShapeFacade.h"
#include <iostream>
#include "../Enums/ShapeEnum.h"

#define _USE_MATH_DEFINES
#include <math.h>

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
* \namespace PhysicsCollision
* \brief Namespace for the physics collision engine
*/
namespace PhysicsCollision {
	/**
	* \namespace PhysicsCollision::Models
	* \brief Namespace for the models in the physics collision engine
	*/
	namespace Models {
		/**
		* \class Shape
		* \brief Class contains the data to create a shape
		*/
		class PHYSICSCOLLISION_API Shape {
		private:
			float area(int x1, int y1, int x2, int y2, int x3, int y3);

			/**
			* \brief X position of the Shape
			*/
			int _x;

			/**
			* \brief Y position of the Shape
			*/
			int _y;

			/**
			* \brief Width of the Shape
			*/
			int _width;

			/**
			* \brief Height of the Shape
			*/
			int _height;

			/**
			* \brief Height of the Shape
			*/
			float _angle;

			/**
			* \brief If the Shape is dynamic
			*/
			bool _is_dynamic;

			/**
			* \brief If the Shape is interactable
			*/
			bool _is_interactable;
		protected:
			/**
			* \brief Type of the Shape
			*/
			Enums::ShapeEnum _type;

			/**
			* \brief An instance of the ShapeFacade
			*/
			std::shared_ptr<Facades::ShapeFacade> _shape_facade;
		public:
			Shape(const int x, const int y, const int height, const int width, const bool is_dynamic, const bool is_interactable, const Enums::ShapeEnum type);

			/**
			* \brief Returns the ShapeFacade
			*/
			std::shared_ptr<Facades::ShapeFacade> get_shape_facade() const;

			/**
			* \brief Returns the type
			*/
			Enums::ShapeEnum get_type() const;

			/**
			* \brief Sets the type the Shape
			*/
			void set_type(Enums::ShapeEnum type);

			/**
			* \brief Sets if the Shape is interactable
			*/
			void set_is_interactable(bool is_interactable);

			/**
			* \brief Sets the X position of the Shape
			*/
			void set_x(float x);

			/**
			* \brief Set the Y position of the Shape
			*/
			void set_y(float y);

			/**
			* \brief Set the width of the Shape
			*/
			void set_width(float width);

			/**
			* \brief Set the width of the Shape
			*/
			void set_angle(float angle);

			/**
			* \brief Set the height of the Shape
			*/
			void set_height(float height);

			/**
			* \brief Returns the X position of the Shape
			*/
			float get_x() const;

			/**
			* \brief Returns the Y position of the Shape
			*/
			float get_y() const;

			/**
			* \brief Returns the width of the Shape
			*/
			float get_width() const;

			/**
			* \brief Returns the height of the Shape
			*/
			float get_height() const;

			/**
			* \brief Move the X position of the Shape
			* \param value -1 is left, 1 is right
			*/
			void move_x(const int value) const;

			/**
			* \brief Move the Y position of the Shape
			*/
			void move_y() const;

			/**
			* \brief Returns the angle of the Shape
			*/
			float get_angle() const;

			/**
			* \brief Returns if the Shape is dynamic
			*/
			bool get_is_dynamic() const;

			/**
			* \brief Returns if the Shape is interactable
			*/
			bool get_is_interactable() const;

			/**
			* \brief Sets if the Shape is dynamic
			*/
			void set_is_dynamic(bool is_dynamic);

			/**
			* \brief Checks if the Shape has collision with another shape
			* \return True if collision, otherwise false
			*/
			bool check_square_collision(std::shared_ptr<Models::Shape> shape);

			/**
			* \brief Checks if the Shape has collision with another shape
			* \return True if collision, otherwise false
			*/
			bool check_polygon_collision(std::shared_ptr<Models::Shape> shape);
      
			/**
			* Returns true when there is collision between the bottom of current shape en the top of the other shape. Else returns false
			*/
			bool check_bottom_collision(std::shared_ptr<Models::Shape> shape);

			bool check_triangle_collision(std::shared_ptr<Models::Shape> shape);
		};
	}
}
