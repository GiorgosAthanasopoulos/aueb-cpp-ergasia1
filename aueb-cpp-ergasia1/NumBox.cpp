#include "NumBox.h"
#include "Metrics.h"

NumBox::NumBox(float x, float y, float w, float h, std::string hint, std::string defaultValue) : Widget(x, y, w, h)
{
	this->hint = hint;
	txt = defaultValue;
	init();
}

void NumBox::init()
{
	br.fill_color[0] = 0;
	br.fill_color[1] = 0;
	br.fill_color[2] = 0;
	br.outline_width = 2;

	lastTime = graphics::getGlobalTime();
}

void NumBox::draw()
{
	if (active)
	{
		graphics::drawRect(x, y, w, h, br);
		graphics::setFont("assets/FiraCode-Regular.ttf");
		graphics::drawText(x - w / 2 + TEXT_OFFSET, y + TEXT_OFFSET, 20, txt, br_txt);
		graphics::setFont(OPENSANS);
		if (hint != "")
			graphics::drawText(x - w / 2, y - h / 2 - HINT_OFFSET, 20, hint, br_txt);
	}
}

void NumBox::update()
{
	if (active)
	{
		graphics::MouseState ms;
		graphics::getMouseState(ms);

		float cur_x = graphics::windowToCanvasX((float)ms.cur_pos_x);
		float cur_y = graphics::windowToCanvasY((float)ms.cur_pos_y);

		if (graphics::getGlobalTime() - lastTime > 500)
		{
			lastCode = graphics::SCANCODE_A;
			lastTime = graphics::getGlobalTime();
		}

		if (cur_x <= x + w / 2 && cur_x >= x - w / 2 && cur_y <= y + h / 2 && cur_y >= y - h / 2)
		{
			for (int i = graphics::SCANCODE_1; i < graphics::SCANCODE_RETURN; ++i)
			{
				graphics::scancode_t code = static_cast<graphics::scancode_t>(i);
				if (graphics::getKeyState(code) && txt.length() < MAX_SIZE && code != lastCode && graphics::getGlobalTime() - lastTime > 100)
				{
					if (txt == "0")
						txt = "";
					txt += codes.at(code);
					lastCode = code;
				}
			}
			if (graphics::getKeyState(graphics::SCANCODE_BACKSPACE) && lastCode != graphics::SCANCODE_BACKSPACE)
			{
				txt = txt.substr(0, txt.length() - 1);
				if (graphics::getKeyState(graphics::SCANCODE_LCTRL))
					txt = "";
				if (txt == "")
					txt = "0";
				lastCode = graphics::SCANCODE_BACKSPACE;
			}
		}
	}

}

std::string NumBox::getText()
{
	return txt;
}