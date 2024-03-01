#include "Navbar.h"
#include "Label.h"

#include <list>

Navbar::Navbar(float x, float y, float w, float h, graphics::Brush br, std::list<std::shared_ptr<Button>> children) : WidgetGroup(x, y, w, h, children)
{
	this->br = br;
	init();
}

void Navbar::init() {}

void Navbar::draw()
{
	if (active)
	{
		graphics::drawRect(x, y, w, h, br);

		for (std::list<std::shared_ptr<Widget>>::iterator it = children.begin(); it != children.end(); ++it)
			if ((*it)->isActive())
				(*it)->draw();
	}
}

void Navbar::update()
{
	if (active)
		for (std::list<std::shared_ptr<Widget>>::iterator it = children.begin(); it != children.end(); ++it)
			if ((*it)->isActive())
				(*it)->update();
}
