#pragma once

#include "WidgetGroup.h"
#include "graphics.h"
#include "Card.h"

class CardCarousel : public WidgetGroup
{
protected:
	std::list<std::shared_ptr<Card>> cards;
public:
	CardCarousel(float x, float y, float w, float h, std::list<std::shared_ptr<Card>> cards);

	void init();
	void draw();
	void update();
};
