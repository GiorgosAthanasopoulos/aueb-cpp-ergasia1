#include "Widget.h"

#include <string>

Widget::Widget(float x, float y, float w, float h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->active = true;
}

void Widget::setActive(bool active)
{
	this->active = active;
}

bool Widget::isActive()
{
	return active;
}
