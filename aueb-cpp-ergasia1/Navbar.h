#pragma once

#include "WidgetGroup.h"
#include "graphics.h"

class Navbar : public WidgetGroup
{
protected:
	graphics::Brush br;
public:
	Navbar(float x, float y, float w, float h, graphics::Brush br, std::list<std::shared_ptr<Button>> children);

	void init();
	void draw();
	void update();
};
