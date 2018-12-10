#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Box2D/Box2D.h>

constexpr char* WINDOW_TITLE = { "The Game" };
constexpr unsigned int WINDOW_WIDTH = { 800 };
constexpr unsigned int WINDOW_HEIGHT = { 600 };

constexpr float FPS{ 60.0f };
constexpr float ANIMATION_SPEED{ 12.0f };

constexpr float WALK_ACCELERATION{ 500.0f };

/************ Physics Settings ************/
constexpr float PIXEL_PER_METER{ 33.0f };
constexpr float32 TIME_STEP{ 1.0f / FPS }; //the length of time passed to simulate (seconds)
constexpr int32 VELOCITY_ITERATIONS{ 6 };   //how strongly to correct velocity
constexpr int32 POSITION_ITERATIONS{ 2 };   //how strongly to correct position

/* Physics Catergories */
constexpr uint16 PLAYER        { 0b0000000010 };
constexpr uint16 DOOR_KEY      { 0b0000000100 };
constexpr uint16 UNLOCKED_DOOR { 0b0000001000 };

/* Helper functions to create a physics body */
b2Body* CreateSquarePhysicsBody(b2World& world,
								sf::Vector2f position,
								sf::Vector2f size = {0.45f, 0.45f},
								b2BodyType type = b2_staticBody);

b2Body* CreateCirclePhysicsBody(b2World& world,
								sf::Vector2f position,
								float radius,
								b2BodyType type = b2_staticBody);


/************ Texures - Animations ************/
const std::string ANIMATION_TEXTURES[]{"walk_up.png", "walk_down.png", "walk_right.png", "walk_left.png",
									   "idle_up.png", "idle_down.png","idle_right.png","idle_left.png" };

#endif // !UTIL_HPP
