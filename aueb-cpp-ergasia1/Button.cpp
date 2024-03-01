#include "Button.h"
#include "Metrics.h"

#include <functional>

Button::Button(float x, float y, float w, float h, graphics::Brush brRect, graphics::Brush brText, std::string const text, float textOffsetX, float textOffsetY, graphics::Brush brRectHover, graphics::Brush brTextHover, std::function<void(void)> onclick, std::string hoverSound, std::string clickSound) : Widget(x, y, w, h)
{
	brRectOg = brRect;
	brTextOg = brText;
	this->brRect = brRect;
	this->brText = brText;
	this->text = text;
	this->textOffsetX = textOffsetX;
	this->textOffsetY = textOffsetY;
	this->brRectHover = brRectHover;
	this->brTextHover = brTextHover;
	this->onclick = onclick;
	this->hoverSound = hoverSound;
	this->clickSound = clickSound;
	this->hovered_ = false;
	init();
}

void Button::init()
{
	hovered = 0;
	sound = graphics::getGlobalTime();
}

void Button::draw()
{
	if (active)
	{
		graphics::drawRect(x, y, w, h, brRect);
		graphics::drawText(x - textOffsetX, y + textOffsetY, NAVBAR_FONT_SIZE, text, hovered_ ? brTextHover : brText);
	}
}

void Button::update()
{
	graphics::MouseState ms;
	graphics::getMouseState(ms);

	float cur_x = graphics::windowToCanvasX((float)ms.cur_pos_x);
	float cur_y = graphics::windowToCanvasY((float)ms.cur_pos_y);

	if (cur_x <= x + w / 2 && cur_x >= x - w / 2 && cur_y <= y + h / 2 && cur_y >= y - h / 2)
	{
		// we replace original brRect so we need to save the original in a temp variable
		brRect = brRectHover;
		brText = brTextHover;

		this->hovered_ = true;

		hovered++;

		if (hovered == 1)
			// the following if statement exists so that we are not able to spam click or spam hover the buttons that will create audio issues
			if (graphics::getGlobalTime() - sound >= 1000)
			{
				sound = graphics::getGlobalTime();

				graphics::playSound(hoverSound, .4f);
			}

		if (ms.button_left_pressed)
		{
			graphics::playSound(clickSound, .4f);
			onclick();
		}
	}
	else
	{
		brRect = brRectOg;
		brText = brTextOg;
		this->hovered_ = false;
		hovered = 0;
	}
}

void Button::setFgColor(int r, int g, int b)
{
	graphics::Brush br = brText;
	br.fill_color[0] = r;
	br.fill_color[1] = g;
	br.fill_color[2] = b;
	brText = br;
}

void Button::clearFgColor()
{
	brText = brTextOg;
}
