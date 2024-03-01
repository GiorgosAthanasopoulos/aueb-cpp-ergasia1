#include "App.h"

/*
* View: used in the large carousel-scrollview that auto-rotates (top part of the screen)
* Scene: like a route in the web, a scene in the app is every page with content (ertflix scene, search scene, a movie's scene)
* Card: used in the smaller carousel(cardcarousel) with usually 5 cards.
* MovieView: shows the details of a specific movie.
*/

/*
* In this comment segment I'll explain on what basis some of the design decisions where made:
* 
* 1) Why load all the scenes in the initialization stage of the application? Why not dynamically load them as requested?
* A: Mainly for performance. With sgg being mostly a game-development-focused library, it only makes sense to do the <<heavy work>> in the
*	 initialization period (just like in normal games) rather than when the user expects a smooth experience (in game - or in our case: while using
*    the app). The startup time tradeoff is rather small (startup-time ~ 4seconds, including the sgg library's init time) and in exchange we get 
*    a BLAZINGLY fast in app experience. 
* 
* 2) Why not use relative positioning of components / reuseable parameters for customization?
* A: For developer ease-of-use and reusability. The library is quite minimal when it comes down to its api and a lot of customization means a lot
*	 of parameters for each of our components. As an example to create a simple Button with hover visual and sound effects you need: 2 coordinates,
*    2 size-numbers, 4 brushes, a string, 2 offset-floats, a function and 2 filenames (strings). At the same time, although our components are 
*	 tailored for use in this app (mainly) we also try to achieve some level of reusability which means that we have to keep our components as
*    abstract as possible.
*/

int main()
{
	App* app = new App();
	delete app;
	return 0;
}