#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Box2D/Box2D.h>

constexpr char* WINDOW_TITLE = { "The Game" };
constexpr unsigned int WINDOW_WIDTH = { 800 };
constexpr unsigned int WINDOW_HEIGHT = { 600 };

constexpr float FPS{ 60 };
constexpr float ANIMATION_SPEED{ 12 };

constexpr float WALK_ACCELERATION{ 200 };
constexpr int TEXT_SIZE_FOR_TILE{ 10 };

/* Physics Settings */
constexpr float PIXEL_PER_METER{ 32 };
constexpr float32 TIME_STEP{ 1 / 20.0f }; //the length of time passed to simulate (seconds)
constexpr int32 VELOCITY_ITERATIONS = 8;   //how strongly to correct velocity
constexpr int32 POSITION_ITERATIONS = 3;   //how strongly to correct position

#endif // !UTIL_HPP
