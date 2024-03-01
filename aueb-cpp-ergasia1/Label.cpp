#include "Label.h"
#include "graphics.h"
#include "Metrics.h"
#include "App.h"

Label::Label(float x, float y, float w, float h, std::string const text, graphics::Brush br) : Widget(x, y, w, h)
{
	this->text = text;
	this->br = br;
	init();
}

void Label::init() {}

void Label::draw()
{
	if (active)
		graphics::drawText(x, y, NAVBAR_FONT_SIZE, text, br);
}

void Label::update() {}
