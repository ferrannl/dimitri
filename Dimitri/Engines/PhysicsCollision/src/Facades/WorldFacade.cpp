#include "WorldFacade.h"

PhysicsCollision::Facades::WorldFacade::WorldFacade()
{
	b2Vec2 gravity(0.0f, -10.0f);
	_world = std::make_shared<b2World>(gravity);
	_world_bodies = std::map<std::shared_ptr<PhysicsCollision::Models::Shape>, b2Body*>();
	_shapes = std::vector<std::shared_ptr<PhysicsCollision::Models::Shape>>();
	_body = {};
	_polygon = {};
	_bodies = {};
}

void Facades::WorldFacade::destroy_body(std::shared_ptr<Facades::ShapeFacade> shape_facade)
{
	_world->DestroyBody(shape_facade->get_body());
}

void PhysicsCollision::Facades::WorldFacade::add_shape(std::unique_ptr<PhysicsCollision::Models::Shape> shape)
{
	b2FixtureDef fixtureDef;
	b2Body* body;
	b2BodyDef bodyDef;
	b2PolygonShape _shape;
	_shape.SetAsBox(shape->get_width() / 2, shape->get_height() / 2);
	bodyDef.position.Set(shape->get_x() + shape->get_width() / 2, shape->get_y() + shape->get_height() / 2);
	if (shape->get_is_dynamic())
	{
		bodyDef.type = b2_dynamicBody;
		bodyDef.angle = 0;
		body = _world->CreateBody(&bodyDef);
		fixtureDef.shape = &_shape;
		fixtureDef.density = 1.0f;
		body->CreateFixture(&fixtureDef);
	}else {
		body = _world->CreateBody(&bodyDef);
		body->SetType(b2_staticBody);
		body->CreateFixture(&_shape, 0.0f);
	}
	_bodies.push_back(body);
	_shapes.push_back(shape);
	_world_bodies[shape] = body;
	shape->get_shape_facade()->add_body(body);
}


std::vector<std::shared_ptr<PhysicsCollision::Models::Shape>> PhysicsCollision::Facades::WorldFacade::get_shapes()
{
	return _shapes;
}


void PhysicsCollision::Facades::WorldFacade::simulate() const
{
	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 6;
	_world->Step(timeStep, velocityIterations, positionIterations);

	for (auto const& it : _world_bodies)
	{
		std::shared_ptr<Models::Shape> shape = it.first;
		b2Body* body = it.second;

		b2Vec2 position = body->GetPosition();
		float angle = body->GetAngle();
		shape->set_x(body->GetWorldCenter().x - shape->get_width() / 2);
		shape->set_y(body->GetWorldCenter().y + shape->get_height() / 2);

	}
}
