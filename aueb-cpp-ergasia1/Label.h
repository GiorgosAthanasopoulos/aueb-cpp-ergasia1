#pragma once

#include "Widget.h"
#include "graphics.h"

class Label : public Widget
{
protected:
	std::string text;
	graphics::Brush br;

public:
	Label(float x, float y, float w, float h, std::string const text, graphics::Brush br);

	void init();
	void draw();
	void update();
};
