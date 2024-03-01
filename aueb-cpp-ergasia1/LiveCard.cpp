#include "LiveCard.h"
#include "Metrics.h"
#include "Utils.h"

#include <iostream>

LiveCard::LiveCard(float x, float y, float w, float h, std::string time, std::string title, std::string age_restriction, int percentage, std::string filename, std::string url, std::string iconUrl) : WidgetGroup(x, y, w, h, std::list<std::shared_ptr<Widget>>())
{
	this->time = time;
	this->title = title;
	this->age_restriction = age_restriction;
	this->percentage = percentage;
	this->filename = filename;
	this->url = url;
	this->iconUrl = iconUrl;
	init();
}

void LiveCard::init()
{
	play.fill_color[0] = 1;
	play.fill_color[1] = 0;
	play.fill_color[2] = .5f;
	play.outline_opacity = 0;
	icon.outline_opacity = 0;
	icon.texture = filename;
}

// IMPORTANT!: for this class, and this class only we'll use top left oriented coordinates
void LiveCard::draw()
{
	graphics::Brush br;
	graphics::drawText(x, y, 16, time, br);

	graphics::setFont(OPENSANSB);
	graphics::drawText(x, y + TITLE_OFFSET_Y, 20, title, br);

	graphics::setFont(OPENSANS);
	graphics::drawDisk(x + AGE_OFFSET_X, y + TITLE_OFFSET_Y + AGE_OFFSET_Y, AGE_SIZE, br);

	br.fill_color[0] = 0;
	br.fill_color[1] = 0;
	br.fill_color[2] = 0;
	graphics::drawText(x + AGE_OFFSET_X / (float)1.5, y + TITLE_OFFSET_Y * 2, 16, age_restriction, br);

	graphics::drawRect(x - ICON_OFFSET_X, y + ICON_H / 3, ICON_W, ICON_H, icon);

	graphics::drawRect(x + w / 2, y + h - PERCENTAGE_BAR_OFFSET_Y, w, PERCENTAGE_BAR_H, br);

	br.fill_color[0] = 1;
	br.fill_color[1] = 0;
	br.fill_color[2] = .5f;
	graphics::drawRect(x + w / 2, y + h - PERCENTAGE_BAR_OFFSET_Y, w * percentage / 100, PERCENTAGE_BAR_H, br);

	br.fill_color[0] = 1;
	br.fill_color[0] = 1;
	br.fill_color[0] = 1;

	graphics::drawDisk(x + w, y + h / 6, 25, play);
	br.fill_color[0] = 1;
	br.fill_color[1] = 1;
	br.fill_color[2] = 1;
	graphics::drawText(x + w - PLAY_TEXT_OFFSET_X, y + h / 5, 20, ">", br);

	graphics::MouseState ms;
	graphics::getMouseState(ms);
	float cur_x = graphics::windowToCanvasX((float)ms.cur_pos_x);
	float cur_y = graphics::windowToCanvasY((float)ms.cur_pos_y);
	if (cur_x <= x + w + 25 && cur_x >= x + w - 25 && cur_y <= y + h / 6 + 25 && cur_y >= y + h / 6 - 25)
	{
		play.outline_opacity = 1;
		if (ms.button_left_pressed)
			open(url);
	}
	else
		play.outline_opacity = 0;
	if (cur_x <= x - ICON_OFFSET_X + ICON_W && cur_x >= x - ICON_OFFSET_X - ICON_W && cur_y <= y + ICON_H / 3 + ICON_H && cur_y >= y + ICON_H / 3 - ICON_H)
	{
		icon.outline_opacity = 1;
		if (ms.button_left_pressed)
			open(iconUrl);
	}
	else
		icon.outline_opacity = 0;

	for (std::list<std::shared_ptr<Widget>>::iterator it = children.begin(); it != children.end(); ++it)
		if ((*it)->isActive())
			(*it)->draw();
}

void LiveCard::update()
{
	for (std::list<std::shared_ptr<Widget>>::iterator it = children.begin(); it != children.end(); ++it)
		if ((*it)->isActive())
			(*it)->update();
}
