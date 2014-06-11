#ifndef APPLICATION_H
#define APPLICATION_H

#include <SFML\Graphics.hpp>
#include <Thor\Input.hpp>
using thor::Action;

#include <string>
#include <functional>
using namespace std;

template<typename StateList, typename ActionList>
/* Deals with input/window management */
class Application
{
public:

	sf::RenderWindow window;

	thor::ActionMap<ActionList> amap;
	//thor::ActionMap<ActionList>::CallbackSystem cbsys;
	
	StateList appState;

public:
	
	Application()
	{
		window.create(sf::VideoMode(800, 600), "Cosmic Colliders");
	}
	
	
	Application(int width, int height, string title) 
	{
		window.create(sf::VideoMode(width, height), title);
	}
	
	
	
	Application(string initfile);
	//~Application();

	void quit() { window.close(); }						/* Cleans up and stops */

	bool generateInitFile(string filename);				/* Not implemented atm */

	void changeState(StateList as) { appState = as; }
	StateList getState() { return appState;  }
};

#endif