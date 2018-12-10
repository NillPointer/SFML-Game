#include "Util.hpp"

b2Body* CreateSquarePhysicsBody(b2World& world, sf::Vector2f position, sf::Vector2f size, b2BodyType type) {
	b2Body* body;
	b2PolygonShape shape;
	b2FixtureDef fixture;
	b2BodyDef bodyDef;
	bodyDef.type = type;
	bodyDef.position.Set(position.x / PIXEL_PER_METER, position.y / PIXEL_PER_METER);
	body = world.CreateBody(&bodyDef);

	shape.SetAsBox(size.x, size.y);
	fixture.shape = &shape;
	fixture.friction = 0.0f;
	body->CreateFixture(&fixture);
	return body;
}

b2Body* CreateCirclePhysicsBody(b2World& world, sf::Vector2f position, float radius, b2BodyType type) {
	b2Body* body;
	b2CircleShape shape;
	b2FixtureDef fixture;
	b2BodyDef bodyDef;
	bodyDef.type = type;
	bodyDef.position.Set(position.x / PIXEL_PER_METER, position.y / PIXEL_PER_METER);
	body = world.CreateBody(&bodyDef);

	shape.m_radius = radius;
	fixture.shape = &shape;
	fixture.friction = 0.0f;
	body->CreateFixture(&fixture);
	return body;
}