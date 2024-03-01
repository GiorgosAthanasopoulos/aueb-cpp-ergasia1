#pragma once

#include "Widget.h"
#include "graphics.h"

class Image : public Widget
{
protected:
	std::string filename;
	graphics::Brush br;

public:
	Image(float x, float y, float w, float h, std::string const filename, graphics::Brush br);

	void init();
	void draw();
	void update();
};
