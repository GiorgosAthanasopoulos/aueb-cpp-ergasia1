#include "WidgetGroup.h"

WidgetGroup::WidgetGroup(float x, float y, float w, float h, std::list<std::shared_ptr<Widget>> children) : Widget(x, y, w, h)
{
	this->children = children;
}

WidgetGroup::WidgetGroup(float x, float y, float w, float h, std::list<std::shared_ptr<Button>> children) : Widget(x, y, w, h)
{
	this->buttons = buttons;
}
