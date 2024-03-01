#include "App.h"
#include "SceneState.h"
#include "TextBox.h"
#include "Metrics.h"
#include "graphics.h"
#include "MovieView.h"
#include "Scene.h"
#include "Navbar.h"
#include "Button.h"
#include "ScrollView.h"
#include "View.h"
#include "Label.h"
#include "CardCarousel.h"
#include "Card.h"
#include "Movies.h"
#include "LiveCard.h"
#include "Utils.h"
#include "SearchResults.h"

App::App() : WidgetGroup(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, std::list<std::shared_ptr<Widget>>())
{
	// boilerplate init code for sgg
	graphics::createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, APP_TITLE);
	graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);
	graphics::setUserData(this);
	graphics::setDrawFunction(std::bind(&App::draw, this));
	graphics::setUpdateFunction(std::bind(&App::update, this));
	graphics::setFont(OPENSANS);
	init();
	graphics::startMessageLoop();
	graphics::stopMessageLoop();
	graphics::destroyWindow();
}

/*
App::init is where the main chuck of code resides in
*/
void App::init()
{
	graphics::Brush br;
	std::vector<Movie> movies_ = {fading_gigolo, infinitely_polar_bear, a_ciambra, the_weight_of_the_sea, umbrella, the_student};
	std::vector<SceneState> scenes_ = {FADING_GIGOLO, INFINITELY_POLAR_BEAR, A_CIAMBRA, THE_WEIGHT_OF_THE_SEA, UMBRELLA, THE_STUDENT};
	for (int i=0; i<movies_.size(); ++i)
	{
		cards.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 0 + CARD_OFFSET * 0, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, movies_[i], br, [=]() { currentScene = scenes_[i]; })));
	}

	std::list<std::shared_ptr<Widget>> children{};
	std::list<std::shared_ptr<View>> scrollViewChildren{};
	std::list<std::shared_ptr<Card>> cardCarouselChildren{};
	std::list<std::shared_ptr<Card>> cardCarousel2Children{};

	scenes = {};
	currentScene = MAIN;

	// draw bg
	graphics::Brush background;
	background.fill_color[0] = 0.04f;
	background.fill_color[1] = 0.08f;
	background.fill_color[2] = 0.1f;
	graphics::setWindowBackground(background);

	// navbar and navbar buttons
	graphics::Brush title;
	title.fill_color[0] = 0;
	title.fill_color[1] = .8f;
	title.fill_color[2] = .8f;
	graphics::Brush rect, text;
	rect.fill_opacity = 0;
	rect.fill_secondary_opacity = 0;
	rect.outline_opacity = 0;
	graphics::Brush textH;
	textH.fill_color[0] = 1;
	textH.fill_color[1] = 0;
	textH.fill_color[2] = .5f;
	buttons.push_back(std::shared_ptr<Button>(new Button(
		x + 70 + 130 * 0, y + 30, 120, 50, rect, text, APP_TITLE, 50, 10, rect, title, [&]()
		{ currentScene = MAIN; },
		NAVBAR_HOVER, NAVBAR_CLICK)));
	buttons.push_back(std::shared_ptr<Button>(new Button(
		x + 70 + 130 * 1, y + 30, 120, 50, rect, text, "LIVE", 25, 10, rect, textH, [&]()
		{ currentScene = LIVE; },
		NAVBAR_HOVER, NAVBAR_CLICK)));
	buttons.push_back(std::shared_ptr<Button>(new Button(
		x + 70 + 130 * 2, y + 30, 120, 50, rect, text, "SERIES", 40, 10, rect, textH, [&]()
		{ currentScene = SERIES; },
		NAVBAR_HOVER, NAVBAR_CLICK)));
	buttons.push_back(std::shared_ptr<Button>(new Button(
		x + 70 + 130 * 3, y + 30, 120, 50, rect, text, "MOVIES", 50, 10, rect, textH, [&]()
		{ currentScene = MOVIES; },
		NAVBAR_HOVER, NAVBAR_CLICK)));
	buttons.push_back(std::shared_ptr<Button>(new Button(
		x + 70 + 130 * 4, y + 30, 120, 50, rect, text, "DOC", 30, 10, rect, textH, [&]()
		{ currentScene = DOCUMENTARIES; },
		NAVBAR_HOVER, NAVBAR_CLICK)));
	buttons.push_back(std::shared_ptr<Button>(new Button(
		x + 70 + 130 * 5, y + 30, 120, 50, rect, text, "CHILDREN", 62, 10, rect, textH, [&]()
		{ currentScene = CHILDREN; },
		NAVBAR_HOVER, NAVBAR_CLICK)));
	buttons.push_back(std::shared_ptr<Button>(new Button(
		x + 70 + 130 * 6, y + 30, 120, 50, rect, text, "SHOWS", 50, 10, rect, textH, [&]()
		{ currentScene = SHOWS; },
		NAVBAR_HOVER, NAVBAR_CLICK)));
	buttons.push_back(std::shared_ptr<Button>(new Button(
		x + 70 + 130 * 7, y + 30, 120, 50, rect, text, "NEWS", 40, 10, rect, textH, [&]()
		{ currentScene = NEWS; },
		NAVBAR_HOVER, NAVBAR_CLICK)));
	buttons.push_back(std::shared_ptr<Button>(new Button(
		x + 70 + 130 * 8, y + 30, 120, 50, rect, text, "SPORTS", 50, 10, rect, textH, [&]()
		{ currentScene = SPORTS; },
		NAVBAR_HOVER, NAVBAR_CLICK)));
	buttons.push_back(std::shared_ptr<Button>(new Button(
		x + 70 + 130 * 9, y + 30, 120, 50, rect, text, "ARCHIVE", 60, 10, rect, textH, [&]()
		{ currentScene = ARCHIVE; },
		NAVBAR_HOVER, NAVBAR_CLICK)));
	buttons.push_back(std::shared_ptr<Button>(new Button(
		x + 70 + 130 * 10, y + 30, 120, 50, rect, text, "SEARCH", 50, 10, rect, textH, [&]()
		{ currentScene = SEARCH; },
		NAVBAR_HOVER, NAVBAR_CLICK)));
	this->children.push_back(std::shared_ptr<Widget>(new Navbar(0, 0, CANVAS_WIDTH, 66, rect, buttons)));

	// main scene
	children.clear();
	scrollViewChildren.clear();
	cardCarouselChildren.clear();
	cardCarousel2Children.clear();
	scrollViewChildren.push_back(std::shared_ptr<View>(new View(CANVAS_WIDTH / 2, 69 + CANVAS_HEIGHT / 2 / 2, CANVAS_WIDTH, CANVAS_HEIGHT / 2, fading_gigolo, br, this, FADING_GIGOLO)));
	scrollViewChildren.push_back(std::shared_ptr<View>(new View(CANVAS_WIDTH / 2, 69 + CANVAS_HEIGHT / 2 / 2, CANVAS_WIDTH, CANVAS_HEIGHT / 2, infinitely_polar_bear, br, this, INFINITELY_POLAR_BEAR)));
	scrollViewChildren.push_back(std::shared_ptr<View>(new View(CANVAS_WIDTH / 2, 69 + CANVAS_HEIGHT / 2 / 2, CANVAS_WIDTH, CANVAS_HEIGHT / 2, a_ciambra, br, this, A_CIAMBRA)));
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 0 + CARD_OFFSET * 0, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, one_august_night, br, [&]() { currentScene = ONE_AUGUST_NIGHT; })));
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 1 + CARD_OFFSET * 1, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, act_like_youre_asleep, br, [&]() { currentScene = ACT_LIKE_YOURE_ASLEEP; })));
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 2 + CARD_OFFSET * 2, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, the_numbers, br, [&]() { currentScene = THE_NUMBERS; })));
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 3 + CARD_OFFSET * 3, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, flame_and_wind, br, [&]() { currentScene = FLAME_AND_WIND; })));
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 4 + CARD_OFFSET * 4, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, remember_when, br, [&]() { currentScene = REMEMBER_WHEN; })));
	children.push_back(std::shared_ptr<Widget>(new ScrollView(CANVAS_WIDTH / 2, 69 + CANVAS_HEIGHT / 2 / 2, CANVAS_WIDTH, CANVAS_HEIGHT / 2, scrollViewChildren)));
	children.push_back(std::shared_ptr<Widget>(new CardCarousel(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 1.5, CANVAS_WIDTH / 1.5, 100, cardCarouselChildren)));
	scenes[MAIN] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);
	for (std::list<std::shared_ptr<Card>>::iterator it = cardCarouselChildren.begin(); it != cardCarouselChildren.end(); ++it)
		cards.push_back(*it);

	// live scene
	children.clear();
	scrollViewChildren.clear();
	cardCarouselChildren.clear();
	cardCarousel2Children.clear();
	children.push_back(std::shared_ptr<Widget>(new LiveCard(250, 125 * 1, 750, 100, "17:40-17:50", "Enimerosi-Thanos Siafakas, Kostas Laskaratos*Enimerosi(Ekpompi)", "K", 75, "assets\\ert-news.png", "https://www.ertflix.gr/en/epg/audition/prg.236786-ert-news-3846486", "https://www.ertflix.gr/en/epg/channel/ert-news")));
	children.push_back(std::shared_ptr<Widget>(new LiveCard(250, 125 * 2, 750, 100, "16:00-19:00", "Studio 4[K8]*Psixagogia(Ekpompi)", "8", 66, "assets\\ert-1.png", "https://www.ertflix.gr/en/epg/audition/prg.236651-ept1-live-3844856", "https://www.ertflix.gr/en/epg/channel/ept1-live")));
	children.push_back(std::shared_ptr<Widget>(new LiveCard(250, 125 * 3, 750, 100, "17:00-18:00", "Ekpliktika Ksenodoxeia-G Kyklos(E)[K8]*Ntokimanter(Tajidia)<<Londino>>", "8", 95, "assets\\ert-2.png", "https://www.ertflix.gr/en/epg/audition/prg.236680-ept2-live-3844746", "https://www.ertflix.gr/en/epg/channel/ept2-live")));
	children.push_back(std::shared_ptr<Widget>(new LiveCard(250, 125 * 4, 750, 100, "17:45-18:00", "O Kairos me ton Saki Arnaoutoglou*Enimerosi", "K", 85, "assets\\ert-3.png", "https://www.ertflix.gr/en/epg/audition/prg.236705-ept3-live-2-3847180", "https://www.ertflix.gr/en/epg/channel/ept3-live-2")));
	children.push_back(std::shared_ptr<Widget>(new LiveCard(250, 125 * 5, 750, 100, "19:00-18:00", "07/01/2023|17:00|Basket League:Ionikos-Karditsa Biologiko Xorio(11i Agonistiki)", "", 85, "assets\\ert-sport-1.png", "https://www.ertflix.gr/en/epg/audition/prg.236611-07-01-2023-1700-basket-league-ionikos-karditsa-biologiko-khorio-11e-agonistike", "https://www.ertflix.gr/en/epg/channel/ert-sports-live-ww")));
	children.push_back(std::shared_ptr<Widget>(new LiveCard(250, 125 * 6, 750, 100, "18:00-17:00", "07/01/2023|17:00-18:15 A1 POLO|13i Agonistiko, Panathinaikos-Panionios(Z)", "", 95, "assets\\ert-sport-2.png", "https://www.ertflix.gr/en/epg/audition/prg.236165-07-01-2023-1700-1815-a1-polo-13e-agonistike-panathenaikos-panionios-z", "https://www.ertflix.gr/en/epg/channel/ert-sports-2-live-ww")));
	children.push_back(std::shared_ptr<Widget>(new LiveCard(250, 125 * 7, 750, 100, "17:30-18:00", "Carousel(E)[K8]*Mousika(Tileperiodiko)<<World Music>>", "8", 95, "assets\\ert-world.png", "https://www.ertflix.gr/en/epg/audition/prg.236730-ept-world-live-3847929", "https://www.ertflix.gr/en/epg/channel/ept-world-live")));
	scenes[LIVE] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	// series scene
	children.clear();
	scrollViewChildren.clear();
	cardCarouselChildren.clear();
	cardCarousel2Children.clear();
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 0 + CARD_OFFSET * 0, CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, apple_tree_yard, br, [&]() { currentScene = APPLE_TREE_YARD; })));
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 1 + CARD_OFFSET * 1, CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, one_captain, br, [&]() { currentScene = ONE_CAPTAIN; })));
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 2 + CARD_OFFSET * 2, CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, zero_zero_zero, br, [&]() { currentScene = ZERO_ZERO_ZERO; })));
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 3 + CARD_OFFSET * 3, CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, the_collapse, br, [&]() { currentScene = THE_COLLAPSE; })));
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 4 + CARD_OFFSET * 4, CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, dicte, br, [&]() { currentScene = DICTE; })));
	cardCarousel2Children.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 0 + CARD_OFFSET * 0, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, the_gulf, br, [&]() { currentScene = THE_GULF; })));
	cardCarousel2Children.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 1 + CARD_OFFSET * 1, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, dos_vidas, br, [&]() { currentScene = DOS_VIDAS; })));
	cardCarousel2Children.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 2 + CARD_OFFSET * 2, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, la_garconne, br, [&]() { currentScene = LA_GARCONNE; })));
	cardCarousel2Children.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 3 + CARD_OFFSET * 3, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, criminal_games, br, [&]() { currentScene = CRIMINAL_GAMES; })));
	cardCarousel2Children.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 4 + CARD_OFFSET * 4, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, love_in_chains, br, [&]() { currentScene = LOVE_IN_CHAINS; })));
	children.push_back(std::shared_ptr<Widget>(new CardCarousel(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 1.5, CANVAS_WIDTH / 1.5, 100, cardCarouselChildren)));
	children.push_back(std::shared_ptr<Widget>(new CardCarousel(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 1.5, CANVAS_WIDTH / 1.5, 100, cardCarousel2Children)));
	scenes[SERIES] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);
	for (std::list<std::shared_ptr<Card>>::iterator it = cardCarouselChildren.begin(); it != cardCarouselChildren.end(); ++it)
		cards.push_back(*it);
	for (std::list<std::shared_ptr<Card>>::iterator it = cardCarousel2Children.begin(); it != cardCarousel2Children.end(); ++it)
		cards.push_back(*it);

	// movies scene
	children.clear();
	scrollViewChildren.clear();
	cardCarouselChildren.clear();
	cardCarousel2Children.clear();
	scrollViewChildren.push_back(std::shared_ptr<View>(new View(CANVAS_WIDTH / 2, 69 + CANVAS_HEIGHT / 2 / 2, CANVAS_WIDTH, CANVAS_HEIGHT / 2, the_weight_of_the_sea, br, this, THE_WEIGHT_OF_THE_SEA)));
	scrollViewChildren.push_back(std::shared_ptr<View>(new View(CANVAS_WIDTH / 2, 69 + CANVAS_HEIGHT / 2 / 2, CANVAS_WIDTH, CANVAS_HEIGHT / 2, umbrella, br, this, UMBRELLA)));
	scrollViewChildren.push_back(std::shared_ptr<View>(new View(CANVAS_WIDTH / 2, 69 + CANVAS_HEIGHT / 2 / 2, CANVAS_WIDTH, CANVAS_HEIGHT / 2, the_student, br, this, THE_STUDENT)));
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 0 + CARD_OFFSET * 0, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, workday, br, [&]() { currentScene = WORKDAY; })));
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 1 + CARD_OFFSET * 1, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, memory_reloaded, br, [&]() { currentScene = MEMORY_RELOADED; })));
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 2 + CARD_OFFSET * 2, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, largo, br, [&]() { currentScene = LARGO; })));
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 3 + CARD_OFFSET * 3, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, smoke_and_mirrors, br, [&]() { currentScene = SMOKE_AND_MIRRORS; })));
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 4 + CARD_OFFSET * 4, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, the_ardennes, br, [&]() { currentScene = THE_ARDENNES; })));
	children.push_back(std::shared_ptr<Widget>(new ScrollView(CANVAS_WIDTH / 2, 69 + CANVAS_HEIGHT / 2 / 2, CANVAS_WIDTH, CANVAS_HEIGHT / 2, scrollViewChildren)));
	children.push_back(std::shared_ptr<Widget>(new CardCarousel(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 1.5, CANVAS_WIDTH / 1.5, 100, cardCarouselChildren)));
	scenes[MOVIES] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);
	for (std::list<std::shared_ptr<Card>>::iterator it = cardCarouselChildren.begin(); it != cardCarouselChildren.end(); ++it)
		cards.push_back(*it);
			
	// documentaries scene
	children.clear();
	scrollViewChildren.clear();
	cardCarouselChildren.clear();
	cardCarousel2Children.clear();
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 0 + CARD_OFFSET * 0, CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, adventures_on_the_arctic_ice, br, [&]() { currentScene = ADVENTURES_ON_THE_ARCTIC_ICE; })));
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 1 + CARD_OFFSET * 1, CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, legacy, br, [&]() { currentScene = LEGACY; })));
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 2 + CARD_OFFSET * 2, CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, under_thin_ice, br, [&]() { currentScene = UNDER_THIN_ICE; })));
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 3 + CARD_OFFSET * 3, CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, spy_in_the_snow, br, [&]() { currentScene = SPY_IN_THE_SNOW; })));
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 4 + CARD_OFFSET * 4, CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, snow_animals, br, [&]() { currentScene = SNOW_ANIMALS; })));
	cardCarousel2Children.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 0 + CARD_OFFSET * 0, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, reggie_in_china, br, [&]() { currentScene = REGGIE_IN_CHINA; })));
	cardCarousel2Children.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 1 + CARD_OFFSET * 1, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, joanna_lumleys_japan, br, [&]() { currentScene = JOANNA_LUMLEYS_JAPAN; })));
	cardCarousel2Children.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 2 + CARD_OFFSET * 2, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, stephen_fry_in_central_america, br, [&]() { currentScene = STEPHEN_FRY_IN_CENTRAL_AMERICA; })));
	cardCarousel2Children.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 3 + CARD_OFFSET * 3, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, super_cute_animals, br, [&]() { currentScene = SUPER_CUTE_ANIMALS; })));
	cardCarousel2Children.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 4 + CARD_OFFSET * 4, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, my_greek_odyssey, br, [&]() { currentScene = MY_GREEK_ODYSSEY; })));
	children.push_back(std::shared_ptr<Widget>(new CardCarousel(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 1.5, CANVAS_WIDTH / 1.5, 100, cardCarouselChildren)));
	children.push_back(std::shared_ptr<Widget>(new CardCarousel(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 1.5, CANVAS_WIDTH / 1.5, 100, cardCarousel2Children)));
	scenes[DOCUMENTARIES] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);
	for (std::list<std::shared_ptr<Card>>::iterator it = cardCarouselChildren.begin(); it != cardCarouselChildren.end(); ++it)
		cards.push_back(*it);
	for (std::list<std::shared_ptr<Card>>::iterator it = cardCarousel2Children.begin(); it != cardCarousel2Children.end(); ++it)
		cards.push_back(*it);

	// children scene
	children.clear();
	scrollViewChildren.clear();
	cardCarouselChildren.clear();
	cardCarousel2Children.clear();
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 0 + CARD_OFFSET * 0, CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, llama_llama, br, [&]() { currentScene = LLAMA_LLAMA; })));
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 1 + CARD_OFFSET * 1, CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, go_jetters, br, [&]() { currentScene = GO_JETTERS; })));
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 2 + CARD_OFFSET * 2, CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, the_fox_badger_family, br, [&]() { currentScene = THE_FOX_BADGER_FAMILY; })));
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 3 + CARD_OFFSET * 3, CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, super_monsters, br, [&]() { currentScene = SUPER_MONSTERS; })));
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 4 + CARD_OFFSET * 4, CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, hey_duggee, br, [&]() { currentScene = HEY_DUGGEE; })));
	cardCarousel2Children.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 0 + CARD_OFFSET * 0, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, save_your_planet, br, [&]() { currentScene = SAVE_YOUR_PLANET; })));
	cardCarousel2Children.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 1 + CARD_OFFSET * 1, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, martin_morning, br, [&]() { currentScene = MARTIN_MORNING; })));
	cardCarousel2Children.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 2 + CARD_OFFSET * 2, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, yeti_tales, br, [&]() { currentScene = YETI_TALES; })));
	cardCarousel2Children.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 3 + CARD_OFFSET * 3, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, puffin_rock, br, [&]() { currentScene = PUFFIN_ROCK; })));
	cardCarousel2Children.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 4 + CARD_OFFSET * 4, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, jojo_and_gran_gran, br, [&]() { currentScene = JOJO_AND_GRAN_GRAN; })));
	children.push_back(std::shared_ptr<Widget>(new CardCarousel(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 1.5, CANVAS_WIDTH / 1.5, 100, cardCarouselChildren)));
	children.push_back(std::shared_ptr<Widget>(new CardCarousel(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 1.5, CANVAS_WIDTH / 1.5, 100, cardCarousel2Children)));
	scenes[CHILDREN] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);
	for (std::list<std::shared_ptr<Card>>::iterator it = cardCarouselChildren.begin(); it != cardCarouselChildren.end(); ++it)
		cards.push_back(*it);
	for (std::list<std::shared_ptr<Card>>::iterator it = cardCarousel2Children.begin(); it != cardCarousel2Children.end(); ++it)
		cards.push_back(*it);

	// shows scene
	children.clear();
	scrollViewChildren.clear();
	cardCarouselChildren.clear();
	cardCarousel2Children.clear();
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 0 + CARD_OFFSET * 0, CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, _1_2_3_happy_2023, br, [&]() { currentScene = _1_2_3_HAPPY_2023; })));
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 1 + CARD_OFFSET * 1, CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, young_bands, br, [&]() { currentScene = YOUNG_BANDS; })));
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 2 + CARD_OFFSET * 2, CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, morning_time_we_met, br, [&]() { currentScene = MORNING_TIME_WE_MET; })));
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 3 + CARD_OFFSET * 3, CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, say_the_word, br, [&]() { currentScene = SAY_THE_WORD; })));
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 4 + CARD_OFFSET * 4, CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, music_box, br, [&]() { currentScene = MUSIC_BOX; })));
	cardCarousel2Children.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 0 + CARD_OFFSET * 0, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, dangerous, br, [&]() { currentScene = DANGEROUS; })));
	cardCarousel2Children.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 1 + CARD_OFFSET * 1, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, signals, br, [&]() { currentScene = SIGNALS; })));
	cardCarousel2Children.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 2 + CARD_OFFSET * 2, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, monogramma, br, [&]() { currentScene = MONOGRAMMA; })));
	cardCarousel2Children.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 3 + CARD_OFFSET * 3, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, portraits, br, [&]() { currentScene = PORTRAITS; })));
	cardCarousel2Children.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 4 + CARD_OFFSET * 4, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, _365_moments, br, [&]() { currentScene = _365_MOMENTS; })));
	children.push_back(std::shared_ptr<Widget>(new CardCarousel(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 1.5, CANVAS_WIDTH / 1.5, 100, cardCarouselChildren)));
	children.push_back(std::shared_ptr<Widget>(new CardCarousel(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 1.5, CANVAS_WIDTH / 1.5, 100, cardCarousel2Children)));
	scenes[SHOWS] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);
	for (std::list<std::shared_ptr<Card>>::iterator it = cardCarouselChildren.begin(); it != cardCarouselChildren.end(); ++it)
		cards.push_back(*it);
	for (std::list<std::shared_ptr<Card>>::iterator it = cardCarousel2Children.begin(); it != cardCarousel2Children.end(); ++it)
		cards.push_back(*it);

	// news scene
	children.clear();
	scrollViewChildren.clear();
	cardCarouselChildren.clear();
	cardCarousel2Children.clear();
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 0 + CARD_OFFSET * 0, CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, epilogue, br, [&]() { currentScene = EPILOGUE; })));
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 1 + CARD_OFFSET * 1, CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, sunday_evening, br, [&]() { currentScene = SUNDAY_EVENING; })));
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 2 + CARD_OFFSET * 2, CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, in_the_centre, br, [&]() { currentScene = IN_THE_CENTRE; })));
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 3 + CARD_OFFSET * 3, CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, colorful_day, br, [&]() { currentScene = COLORFUL_DAY; })));
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 4 + CARD_OFFSET * 4, CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, connections, br, [&]() { currentScene = CONNECTIONS; })));
	cardCarousel2Children.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 0 + CARD_OFFSET * 0, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, health, br, [&]() { currentScene = HEALTH; })));
	cardCarousel2Children.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 1 + CARD_OFFSET * 1, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, environment, br, [&]() { currentScene = ENVIRONMENT; })));
	cardCarousel2Children.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 2 + CARD_OFFSET * 2, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, without_limitations, br, [&]() { currentScene = WITHOUT_LIMITATIONS; })));
	cardCarousel2Children.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 3 + CARD_OFFSET * 3, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, education, br, [&]() { currentScene = EDUCATION; })));
	cardCarousel2Children.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 4 + CARD_OFFSET * 4, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, production, br, [&]() { currentScene = PRODUCTION; })));
	children.push_back(std::shared_ptr<Widget>(new CardCarousel(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 1.5, CANVAS_WIDTH / 1.5, 100, cardCarouselChildren)));
	children.push_back(std::shared_ptr<Widget>(new CardCarousel(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 1.5, CANVAS_WIDTH / 1.5, 100, cardCarousel2Children)));
	scenes[NEWS] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);
	for (std::list<std::shared_ptr<Card>>::iterator it = cardCarouselChildren.begin(); it != cardCarouselChildren.end(); ++it)
		cards.push_back(*it);
	for (std::list<std::shared_ptr<Card>>::iterator it = cardCarousel2Children.begin(); it != cardCarousel2Children.end(); ++it)
		cards.push_back(*it);

	// sports scene
	children.clear();
	scrollViewChildren.clear();
	cardCarouselChildren.clear();
	cardCarousel2Children.clear();
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 0 + CARD_OFFSET * 0, CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, athletic_sunday, br, [&]() { currentScene = ATHLETIC_SUNDAY; })));
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 1 + CARD_OFFSET * 1, CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, the_sports_world, br, [&]() { currentScene = THE_SPORTS_WORLD; })));
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 2 + CARD_OFFSET * 2, CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, auto_moto_ert, br, [&]() { currentScene = AUTO_MOTO_ERT; })));
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 3 + CARD_OFFSET * 3, CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, years_of_innocence, br, [&]() { currentScene = YEARS_OF_INNOCENCE; })));
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 4 + CARD_OFFSET * 4, CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, memories_from_sports, br, [&]() { currentScene = MEMORIES_FROM_SPORTS; })));
	cardCarousel2Children.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 0 + CARD_OFFSET * 0, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, super_league_2_2022_2023, br, [&]() { currentScene = SUPER_LEAGUE_2_2022_2023; })));
	cardCarousel2Children.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 1 + CARD_OFFSET * 1, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, basket_league_2022_2023, br, [&]() { currentScene = BASKET_LEAGUE_2022_2023; })));
	cardCarousel2Children.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 2 + CARD_OFFSET * 2, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, volley_league_2022_23, br, [&]() { currentScene = VOLLEY_LEAGUE_2022_23; })));
	cardCarousel2Children.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 3 + CARD_OFFSET * 3, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, run_greece_2022, br, [&]() { currentScene = RUN_GREECE_2022; })));
	cardCarousel2Children.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 4 + CARD_OFFSET * 4, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, polo_len_champions_league, br, [&]() { currentScene = POLO_LEN_CHAMPIONS_LEAGUE; })));
	children.push_back(std::shared_ptr<Widget>(new CardCarousel(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 1.5, CANVAS_WIDTH / 1.5, 100, cardCarouselChildren)));
	children.push_back(std::shared_ptr<Widget>(new CardCarousel(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 1.5, CANVAS_WIDTH / 1.5, 100, cardCarousel2Children)));
	scenes[SPORTS] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);
	for (std::list<std::shared_ptr<Card>>::iterator it = cardCarouselChildren.begin(); it != cardCarouselChildren.end(); ++it)
		cards.push_back(*it);
	for (std::list<std::shared_ptr<Card>>::iterator it = cardCarousel2Children.begin(); it != cardCarousel2Children.end(); ++it)
		cards.push_back(*it);

	// archive scene
	children.clear();
	scrollViewChildren.clear();
	cardCarouselChildren.clear();
	cardCarousel2Children.clear();
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 0 + CARD_OFFSET * 0, CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, maria_demadi, br, [&]() { currentScene = MARIA_DEMADI; })));
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 1 + CARD_OFFSET * 1, CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, black_chrysalis, br, [&]() { currentScene = BLACK_CHRYSALIS; })));
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 2 + CARD_OFFSET * 2, CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, the_children_of_niobe_the_series, br, [&]() { currentScene = THE_CHILDREN_OF_NIOBE_THE_SERIES; })));
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 3 + CARD_OFFSET * 3, CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, the_children_of_niobe_the_tv_movies, br, [&]() { currentScene = THE_CHILDREN_OF_NIOBE_THE_TV_MOVIES; })));
	cardCarouselChildren.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 4 + CARD_OFFSET * 4, CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, drifting_cities, br, [&]() { currentScene = DRIFTING_CITIES; })));
	cardCarousel2Children.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 0 + CARD_OFFSET * 0, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, invalids_and_wayfarers, br, [&]() { currentScene = INVALIDS_AND_WAYFARERS; })));
	cardCarousel2Children.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 1 + CARD_OFFSET * 1, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, fruitopia, br, [&]() { currentScene = FRUITOPIA; })));
	cardCarousel2Children.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 2 + CARD_OFFSET * 2, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, o_paramithas, br, [&]() { currentScene = O_PARAMITHAS; })));
	cardCarousel2Children.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 3 + CARD_OFFSET * 3, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, the_treasure_of_vagia, br, [&]() { currentScene = THE_TREASURE_OF_VAGIA; })));
	cardCarousel2Children.push_back(std::shared_ptr<Card>(new Card(CARD_CAROUSEL_OFFSETX + CARD_WIDTH * 4 + CARD_OFFSET * 4, CANVAS_HEIGHT - CARD_CAROUSEL_OFFSETY, CARD_WIDTH, CARD_HEIGHT, wildcat_under_glass, br, [&]() { currentScene = WILDCAT_UNDER_GLASS; })));
	children.push_back(std::shared_ptr<Widget>(new CardCarousel(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 1.5, CANVAS_WIDTH / 1.5, 100, cardCarouselChildren)));
	children.push_back(std::shared_ptr<Widget>(new CardCarousel(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 1.5, CANVAS_WIDTH / 1.5, 100, cardCarousel2Children)));
	scenes[ARCHIVE] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);
	for (std::list<std::shared_ptr<Card>>::iterator it = cardCarouselChildren.begin(); it != cardCarouselChildren.end(); ++it)
		cards.push_back(*it);
	for (std::list<std::shared_ptr<Card>>::iterator it = cardCarousel2Children.begin(); it != cardCarousel2Children.end(); ++it)
		cards.push_back(*it);

	// search scene
	children.clear();
	children.push_back(std::shared_ptr<Widget>(new SearchResults(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, cards)));
	scenes[SEARCH] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	// the following part of code in App::init is for all the specific movies
	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, fading_gigolo, "black")));
	scenes[FADING_GIGOLO] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, infinitely_polar_bear, "")));
	scenes[INFINITELY_POLAR_BEAR] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, a_ciambra, "")));
	scenes[A_CIAMBRA] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, one_august_night, "")));
	scenes[ONE_AUGUST_NIGHT] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, act_like_youre_asleep, "black")));
	scenes[ACT_LIKE_YOURE_ASLEEP] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, the_numbers, "")));
	scenes[THE_NUMBERS] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, flame_and_wind, "")));
	scenes[FLAME_AND_WIND] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new Label(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, 0, 0, "Remember when", br)));
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, remember_when, "")));
	scenes[REMEMBER_WHEN] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, the_weight_of_the_sea, "")));
	scenes[THE_WEIGHT_OF_THE_SEA] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, umbrella, "black")));
	scenes[UMBRELLA] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, the_student, "")));
	scenes[THE_STUDENT] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, workday, "")));
	scenes[WORKDAY] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, memory_reloaded, "black")));
	scenes[MEMORY_RELOADED] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, largo, "")));
	scenes[LARGO] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, smoke_and_mirrors, "")));
	scenes[SMOKE_AND_MIRRORS] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, the_ardennes, "")));
	scenes[THE_ARDENNES] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, saras_notebook, "")));
	scenes[SARAS_NOTEBOOK] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, wednesday_4_45, "")));
	scenes[WEDNESDAY_4_45] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, adventures_on_the_arctic_ice, "black")));
	scenes[ADVENTURES_ON_THE_ARCTIC_ICE] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, legacy, "")));
	scenes[LEGACY] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, under_thin_ice, "black")));
	scenes[UNDER_THIN_ICE] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, spy_in_the_snow, "black")));
	scenes[SPY_IN_THE_SNOW] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, snow_animals, "black")));
	scenes[SNOW_ANIMALS] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, reggie_in_china, "")));
	scenes[REGGIE_IN_CHINA] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, joanna_lumleys_japan, "")));
	scenes[JOANNA_LUMLEYS_JAPAN] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, stephen_fry_in_central_america, "")));
	scenes[STEPHEN_FRY_IN_CENTRAL_AMERICA] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, super_cute_animals, "")));
	scenes[SUPER_CUTE_ANIMALS] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, my_greek_odyssey, "black")));
	scenes[MY_GREEK_ODYSSEY] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, apple_tree_yard, "")));
	scenes[APPLE_TREE_YARD] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, one_captain, "black")));
	scenes[ONE_CAPTAIN] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, zero_zero_zero, "black")));
	scenes[ZERO_ZERO_ZERO] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, the_collapse, "")));
	scenes[THE_COLLAPSE] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, dicte, "black")));
	scenes[DICTE] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, the_gulf, "")));
	scenes[THE_GULF] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, dos_vidas, "")));
	scenes[DOS_VIDAS] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, la_garconne, "")));
	scenes[LA_GARCONNE] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, criminal_games, "")));
	scenes[CRIMINAL_GAMES] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, love_in_chains, "")));
	scenes[LOVE_IN_CHAINS] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, llama_llama, "")));
	scenes[LLAMA_LLAMA] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, go_jetters, "")));
	scenes[GO_JETTERS] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, the_fox_badger_family, "black")));
	scenes[THE_FOX_BADGER_FAMILY] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, super_monsters, "")));
	scenes[SUPER_MONSTERS] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, hey_duggee, "")));
	scenes[HEY_DUGGEE] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, save_your_planet, "")));
	scenes[SAVE_YOUR_PLANET] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, martin_morning, "")));
	scenes[MARTIN_MORNING] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, yeti_tales, "")));
	scenes[YETI_TALES] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, puffin_rock, "")));
	scenes[PUFFIN_ROCK] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, jojo_and_gran_gran, "")));
	scenes[JOJO_AND_GRAN_GRAN] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, _1_2_3_happy_2023, "")));
	scenes[_1_2_3_HAPPY_2023] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, young_bands, "")));
	scenes[YOUNG_BANDS] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, morning_time_we_met, "black")));
	scenes[MORNING_TIME_WE_MET] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, say_the_word, "black")));
	scenes[SAY_THE_WORD] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, music_box, "")));
	scenes[MUSIC_BOX] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, dangerous, "")));
	scenes[DANGEROUS] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, signals, "")));
	scenes[SIGNALS] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, monogramma, "")));
	scenes[MONOGRAMMA] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, portraits, "black")));
	scenes[PORTRAITS] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, _365_moments, "")));
	scenes[_365_MOMENTS] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, epilogue, "")));
	scenes[EPILOGUE] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, sunday_evening, "")));
	scenes[SUNDAY_EVENING] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, in_the_centre, "")));
	scenes[IN_THE_CENTRE] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, colorful_day, "")));
	scenes[COLORFUL_DAY] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, connections, "")));
	scenes[CONNECTIONS] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, health, "")));
	scenes[HEALTH] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, environment, "")));
	scenes[ENVIRONMENT] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, without_limitations, "")));
	scenes[WITHOUT_LIMITATIONS] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, education, "black")));
	scenes[EDUCATION] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, production, "")));
	scenes[PRODUCTION] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, maria_demadi, "")));
	scenes[MARIA_DEMADI] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, black_chrysalis, "")));
	scenes[BLACK_CHRYSALIS] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, the_children_of_niobe_the_series, "")));
	scenes[THE_CHILDREN_OF_NIOBE_THE_SERIES] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, the_children_of_niobe_the_tv_movies, "")));
	scenes[THE_CHILDREN_OF_NIOBE_THE_TV_MOVIES] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, drifting_cities, "black")));
	scenes[DRIFTING_CITIES] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, invalids_and_wayfarers, "")));
	scenes[INVALIDS_AND_WAYFARERS] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, fruitopia, "")));
	scenes[FRUITOPIA] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, o_paramithas, "black")));
	scenes[O_PARAMITHAS] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, tales_from_the_fairytale_box, "")));
	scenes[TALES_FROM_THE_FAIRYTALE_BOX] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, the_treasure_of_vagia, "")));
	scenes[THE_TREASURE_OF_VAGIA] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, wildcat_under_glass, "")));
	scenes[WILDCAT_UNDER_GLASS] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, athletic_sunday, "")));
	scenes[ATHLETIC_SUNDAY] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, the_sports_world, "")));
	scenes[THE_SPORTS_WORLD] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, auto_moto_ert, "")));
	scenes[AUTO_MOTO_ERT] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, years_of_innocence, "black")));
	scenes[YEARS_OF_INNOCENCE] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, memories_from_sports, "")));
	scenes[MEMORIES_FROM_SPORTS] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, super_league_2_2022_2023, "")));
	scenes[SUPER_LEAGUE_2_2022_2023] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, basket_league_2022_2023 , "black")));
	scenes[BASKET_LEAGUE_2022_2023] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, volley_league_2022_23, "")));
	scenes[VOLLEY_LEAGUE_2022_23] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, run_greece_2022, "")));
	scenes[RUN_GREECE_2022] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);

	children.clear();
	children.push_back(std::shared_ptr<Widget>(new MovieView(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2 + 66, CANVAS_WIDTH, CANVAS_HEIGHT, polo_len_champions_league, "")));
	scenes[POLO_LEN_CHAMPIONS_LEAGUE] = Scene(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, children);
}

void App::draw()
{
	for (std::list<std::shared_ptr<Widget>>::iterator it = children.begin(); it != children.end(); ++it)
		if ((*it)->isActive())
			(*it)->draw();

	for (std::list<std::shared_ptr<Button>>::iterator it = buttons.begin(); it != buttons.end(); ++it)
		if ((*it)->isActive())
			(*it)->draw();

	scenes[currentScene].draw();
}

void App::update()
{
	for (std::list<std::shared_ptr<Widget>>::iterator it = children.begin(); it != children.end(); ++it)
		if ((*it)->isActive())
			(*it)->update();

	for (std::list<std::shared_ptr<Button>>::iterator it = buttons.begin(); it != buttons.end(); ++it)
		if ((*it)->isActive())
			(*it)->update();

	for (int state = MAIN; state <= SEARCH; state++)
		if (state == currentScene)
			getButtonFromList(buttons, state)->setFgColor(1, 0.64f, 0);
		else
			getButtonFromList(buttons, state)->clearFgColor();

	scenes[currentScene].update();
}

void App::setScene(SceneState scene)
{
	currentScene = scene;
}

