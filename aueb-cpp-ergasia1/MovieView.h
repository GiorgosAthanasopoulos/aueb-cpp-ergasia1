#pragma once

#include "WidgetGroup.h"
#include "Movie.h"
#include "graphics.h"

#define CARD_OFFSETX 50
#define CARD_OFFSETY 50
#define CARD_WIDTH_MV 500
#define CARD_HEIGHT_MV 750

#define TITLE_OFFSETX 200
#define TITLE_OFFSETY 180

#define GENRES_OFFSETY 140

#define BUTTON_OFFSETX 250
#define BUTTON_OFFSETY 200
#define BUTTON_WIDTH 100
#define BUTTON_HEIGHT 50
#define WATCH_OFFSETX 45
#define WATCH_OFFSETY 10

class MovieView : public WidgetGroup 
{
protected:
	Movie movie;
	std::string titleFgColor;

	graphics::Brush banner, card, title, button, watch, hover;
public:
	MovieView(float x, float y, float w, float h, Movie movie, std::string titleFgColor);

	void init();
	void draw();
	void update();
};
