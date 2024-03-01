#pragma once

#include <functional>
#include <memory>
#include <list>
#include <map>

#include "WidgetGroup.h"
#include "SceneState.h"
#include "Scene.h"
#include "Widget.h"
#include "Button.h"
#include "Card.h"

#define NAVBAR_CLICK "assets/navbar-click.wav"
#define NAVBAR_HOVER "assets/navbar-hover.wav"

#define WINDOW_WIDTH 1440
#define WINDOW_HEIGHT 950

#define APP_TITLE "ERTFLIX"

#define ASSETS "assets/"

#define CARD_CAROUSEL_OFFSETX 200
#define CARD_CAROUSEL_OFFSETY 250
#define CARD_WIDTH 500/2.5
#define CARD_HEIGHT 750/3
#define CARD_OFFSET 50

class App : public WidgetGroup
{
protected:
	std::map<SceneState, Scene> scenes;
	SceneState currentScene;

	std::list<std::shared_ptr<Card>> cards;
	std::list<std::shared_ptr<Button>> buttons;
public:
	App();

	void init();
	void draw();
	void update();

	void setScene(SceneState scene);
};
