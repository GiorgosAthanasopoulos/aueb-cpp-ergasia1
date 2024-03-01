#include "Card.h"
#include "Metrics.h"

Card::Card(float x, float y, float w, float h, Movie movie, graphics::Brush br, std::function<void(void)> onclick) : Widget(x, y, w, h)
{
	this->movie = movie;
	this->br = br;
	this->onclick = onclick;
	init();
}

void Card::init() {}

void Card::draw()
{
	if (active)
	{
		br.texture = movie.getFilenameCard();
		graphics::drawRect(x, y, w, h, br);
	}
}

void Card::update()
{
	if (active)
	{
		graphics::MouseState ms;
		graphics::getMouseState(ms);

		float cur_x = graphics::windowToCanvasX(ms.cur_pos_x);
		float cur_y = graphics::windowToCanvasY(ms.cur_pos_y);

		br.outline_opacity = 0;

		if (cur_x <= x + w / 2 && cur_x >= x - w / 2 && cur_y <= y + h / 2 && cur_y >= y - h / 2)
		{
			br.outline_opacity = 1;

			graphics::setFont(OPENSANSB);
			// draw title
			graphics::drawText(CARD_OFFSETX, CANVAS_HEIGHT - CARD_OFFSETY * 2, CARD_FONT_SIZE, movie.getName(), br);
			graphics::setFont(OPENSANSL);
			// draw description
			graphics::drawText(CARD_OFFSETX, CANVAS_HEIGHT - CARD_OFFSETY * 1, CARD_FONT_SIZE, movie.getDescription(), br);
			graphics::setFont(OPENSANS);

			if (ms.button_left_pressed)
				onclick();
		}
	}
}

Movie Card::getMovie()
{
	return movie;
}

float Card::getX()
{
	return x;
}

float Card::getY()
{
	return y;
}

void Card::setX(float x)
{
	this->x = x;
}

void Card::setY(float y)
{
	this->y = y;
}

graphics::Brush Card::getBrush()
{
	return br;
}

std::function<void(void)> Card::getOnclick()
{
	return onclick;
}