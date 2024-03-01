#pragma once

#include "WidgetGroup.h"

class Scene : public WidgetGroup
{
public:
	Scene(float x, float y, float w, float h, std::list<std::shared_ptr<Widget>> children);
	Scene();

	void init();
	void draw();
	void update();
};
