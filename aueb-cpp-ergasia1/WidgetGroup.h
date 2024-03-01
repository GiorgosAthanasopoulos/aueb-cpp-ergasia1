#pragma once

#include "Widget.h"
#include "Button.h"

#include <list>
#include <memory>

class WidgetGroup : public Widget
{
protected:
	std::list<std::shared_ptr<Widget>> children;
	std::list<std::shared_ptr<Button>> buttons;
public:
	WidgetGroup(float x, float y, float w, float h, std::list<std::shared_ptr<Widget>> children);
	WidgetGroup(float x, float y, float w, float h, std::list<std::shared_ptr<Button>> children);

	virtual void init() = 0;
	virtual void draw() = 0;
	virtual void update() = 0;
};
