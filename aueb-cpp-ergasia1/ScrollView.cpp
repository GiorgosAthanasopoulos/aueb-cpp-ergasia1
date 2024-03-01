#include "ScrollView.h"
#include "graphics.h"
#include "Button.h"
#include "Metrics.h"

ScrollView::ScrollView(float x, float y, float w, float h, std::list<std::shared_ptr<View>> views) : WidgetGroup(x, y, w, h, std::list<std::shared_ptr<Widget>>())
{
	this->views = views;
	init();
}

void ScrollView::init()
{
	time = graphics::getGlobalTime();
	index = 0;
	temp = 0;
	br.fill_color[0] = 1;
	br.fill_color[1] = 0;
	br.fill_color[2] = .5f;
	br.outline_opacity = 0;
}

/*
Both in ScrollView::draw and ScrollView::update we check a counter temp to make sure we only draw the current view (helps with performance and visual bugs.
*/

void ScrollView::draw()
{
	if (graphics::getGlobalTime() - time >= 5000)
	{
		time = graphics::getGlobalTime();
		index = index + 1 == views.size() ? 0 : index + 1;
	}

	temp = 0;

	for (std::list<std::shared_ptr<View>>::iterator it = views.begin(); it != views.end(); ++it)
	{
		if (temp == index)
		{
			if ((*it)->isActive())
				(*it)->draw();

			graphics::drawRect(x * index, y + CANVAS_HEIGHT / 2 / 2, CANVAS_WIDTH / 3, 5, br);
			break;
		}

		temp++;
	}
}

void ScrollView::update()
{
	temp = 0;

	for (std::list<std::shared_ptr<View>>::iterator it = views.begin(); it != views.end(); ++it)
	{
		if (temp == index)
		{
			if ((*it)->isActive())
				(*it)->update();
			break;
		}

		temp++;
	}
}
