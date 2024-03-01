#include "Image.h"
#include "App.h"
#include "graphics.h"

Image::Image(float x, float y, float w, float h, std::string const filename, graphics::Brush br) : Widget(x, y, w, h)
{
	this->filename = filename;
	this->br = br;
	init();
}

void Image::init()
{
	br.texture = filename;
}

void Image::draw()
{
	if (active)
		graphics::drawRect(x, y, w, h, br);
}

void Image::update() {}
