#pragma once

#include "WidgetGroup.h"
#include "graphics.h"
#include "View.h"

class ScrollView : public WidgetGroup
{
protected:
	std::list<std::shared_ptr<View>> views;
	float time;
	int index, temp;
	graphics::Brush br;
public:
	ScrollView(float x, float y, float w, float h, std::list<std::shared_ptr<View>> children);

	void init();
	void draw();
	void update();
};
