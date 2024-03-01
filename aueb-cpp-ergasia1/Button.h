#pragma once

#include "Widget.h"
#include "graphics.h"

class Button : public Widget
{
protected:
	std::string text, hoverSound, clickSound;
	graphics::Brush brRect, brText, brRectHover, brTextHover, brRectOg, brTextOg;
	float textOffsetX, textOffsetY, sound;
	std::function<void(void)> onclick;
	int hovered;
	bool hovered_;
public:
	Button(float x, float y, float w, float h, graphics::Brush brRect, graphics::Brush brText, std::string const text, float textOffsetX, float textOffsetY, graphics::Brush brRectHover, graphics::Brush brTextHover, std::function<void(void)> onclick, std::string hoverSound, std::string clickSound);

	void init();
	void draw();
	void update();

	void setFgColor(int r, int g, int b);
	void clearFgColor();
};
