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

void SetPhysicsBodyFilter(b2Body* body, uint16 categoryBit, bool isSensor) {
	b2Filter filter = body->GetFixtureList()->GetFilterData();
	filter.categoryBits = categoryBit;
	body->GetFixtureList()->SetFilterData(filter);
	body->GetFixtureList()->SetSensor(isSensor);
}

sf::Vector2f Normalize(sf::Vector2f vector) {
	float length = sqrt((vector.x * vector.x) + (vector.y * vector.y));
	if (length != 0) return sf::Vector2f(vector.x / length, vector.y / length);
	else return vector;
}