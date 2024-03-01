#include "Scene.h"
#include "Metrics.h"
#include "Navbar.h"
#include "Label.h"

Scene::Scene(float x, float y, float w, float h, std::list<std::shared_ptr<Widget>> children) : WidgetGroup(x, y, w, h, children)
{
	init();
}

Scene::Scene() : WidgetGroup(0, 0, 0, 0, std::list<std::shared_ptr<Widget>>())
{
	init();
}

void Scene::init() {}

void Scene::draw()
{
	if (active)
		for (std::list<std::shared_ptr<Widget>>::iterator it = children.begin(); it != children.end(); ++it)
			if ((*it)->isActive())
				(*it)->draw();
}

void Scene::update()
{
	if (active)
		for (std::list<std::shared_ptr<Widget>>::iterator it = children.begin(); it != children.end(); ++it)
			if ((*it)->isActive())
				(*it)->update();
}
