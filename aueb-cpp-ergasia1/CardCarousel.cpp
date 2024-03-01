#include "CardCarousel.h"

CardCarousel::CardCarousel(float x, float y, float w, float h, std::list<std::shared_ptr<Card>> cards) : WidgetGroup(x, y, w, h, std::list<std::shared_ptr<Widget>>())
{
	this->cards = cards;
	init();
}

void CardCarousel::init() {}

void CardCarousel::draw()
{
	for (std::list<std::shared_ptr<Card>>::iterator it = cards.begin(); it != cards.end(); ++it)
		if ((*it)->isActive())
			(*it)->draw();
}

void CardCarousel::update()
{
	for (std::list<std::shared_ptr<Card>>::iterator it = cards.begin(); it != cards.end(); ++it)
		if ((*it)->isActive())
			(*it)->update();
}
