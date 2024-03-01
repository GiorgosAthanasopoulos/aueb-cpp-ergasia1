#pragma once

#include "Widget.h"
#include "Movie.h"
#include "graphics.h"

#define CARD_FONT_SIZE 20
#define CARD_OFFSETX 100
#define CARD_OFFSETY 40

class Card : public Widget
{
protected:
	Movie movie;
	graphics::Brush br;
	std::function<void(void)> onclick;

public:
	Card(float x, float y, float w, float h, Movie movie, graphics::Brush br, std::function<void(void)> onclick);

	void init();
	void draw();
	void update();
	Movie getMovie();

	float getX();
	float getY();
	void setX(float x);
	void setY(float y);
	graphics::Brush getBrush();
	std::function<void(void)> getOnclick();
};
