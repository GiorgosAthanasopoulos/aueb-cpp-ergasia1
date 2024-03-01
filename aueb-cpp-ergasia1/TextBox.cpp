#include "TextBox.h"
#include "Metrics.h"

TextBox::TextBox(float x, float y, float w, float h, std::string hint) : Widget(x, y, w, h)
{
	this->hint = hint;
	init();
}

void TextBox::init()
{
	br.fill_color[0] = 0;
	br.fill_color[1] = 0;
	br.fill_color[2] = 0;
	br.outline_width = 2;

	text = "";

	lastTime = graphics::getGlobalTime();
}

void TextBox::draw()
{
	if (active)
	{
		graphics::drawRect(x, y, w, h, br);
		graphics::setFont("assets/FiraCode-Regular.ttf");
		graphics::drawText(x - w / 2 + TEXT_OFFSET, y + TEXT_OFFSET, 20, text, text_br);
		graphics::setFont(OPENSANS);
		if (hint != "")
			graphics::drawText(x - w / 2, y - h / 2 - HINT_OFFSET, 20, hint, text_br);
	}
}

void TextBox::update()
{
	if (active)
	{
		graphics::MouseState ms;
		graphics::getMouseState(ms);

		float cur_x = graphics::windowToCanvasX((float)ms.cur_pos_x);
		float cur_y = graphics::windowToCanvasY((float)ms.cur_pos_y);

		if (graphics::getGlobalTime()  - lastTime > 500)
		{
			lastCode = graphics::SCANCODE_1;
			lastTime = graphics::getGlobalTime();
		}

		if (cur_x <= x + w / 2 && cur_x >= x - w / 2 && cur_y <= y + h / 2 && cur_y >= y - h / 2)
		{
			for (int i = graphics::SCANCODE_A; i < graphics::SCANCODE_1; ++i)
			{
				graphics::scancode_t code = static_cast<graphics::scancode_t>(i);
				if (graphics::getKeyState(code) && text.length() < MAX_LINE_SIZE && lastCode != code && graphics::getGlobalTime() - lastTime > 100)
				{
					text += codes.at(code);
					lastCode = code;
				}	
			}
			if (graphics::getKeyState(graphics::SCANCODE_BACKSPACE) && lastCode != graphics::SCANCODE_BACKSPACE)
			{
				text = text.substr(0, text.length() - 1);
				if (graphics::getKeyState(graphics::SCANCODE_LCTRL))
					text = "";
				lastCode = graphics::SCANCODE_BACKSPACE;
			}
			else if (graphics::getKeyState(graphics::SCANCODE_SPACE) && text.length() < MAX_LINE_SIZE && lastCode != graphics::SCANCODE_SPACE)
			{
				if (text.substr(text.length() - 1, 1) != " ")
					text += " ";
				lastCode = graphics::SCANCODE_SPACE;
			}
		}
	}
}

std::string TextBox::getText()
{
	return text;
}
