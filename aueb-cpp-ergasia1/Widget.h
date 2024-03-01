#pragma once

class Widget
{
protected:
	float x, y, w, h;
	bool active;
public:
	Widget(float x, float y, float w, float h);

	virtual void init() = 0;
	virtual void draw() = 0;
	virtual void update() = 0;

	void setActive(bool active);
	bool isActive();
};
