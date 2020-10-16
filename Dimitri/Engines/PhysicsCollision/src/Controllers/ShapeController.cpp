#include "ShapeController.h"

Controllers::ShapeController::ShapeController()
{
	_shape_factory = std::make_shared<Factories::ShapeFactory>();
}

std::shared_ptr<Models::Shape> Controllers::ShapeController::create_shape(const std::string type,float x, float y, float width, float height, const bool is_dynamic) const
{
	if (type == "polygon") {
		Models::Polygon polygon;
		polygon.set_height(height);
		polygon.set_width(width);
		polygon.set_x(x);
		polygon.set_y(y);
		polygon.set_is_dynamic(is_dynamic);
		return std::make_shared<Models::Polygon>(is_dynamic);
	}
	//return _shape_factory->create_shape(type,x,y, width, height, is_dynamic);
}