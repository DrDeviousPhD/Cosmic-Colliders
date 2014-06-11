#include <SFML\Graphics.hpp>
#include <Thor\Math.hpp>
#include <Thor\Input.hpp>

#include <iostream>
#include <string>
using namespace std;

#include "Application.h"
#include "Graphics.h"
#include "Object.h"




struct MyBox
{
	sf::Vector2f pos;
	sf::Sprite sprite;

	MyBox();
	MyBox(sf::Texture *tex) : sprite(*tex) {};
	MyBox(sf::Sprite spr) : sprite(spr) {};
};


enum MyState
{
	MAIN_MENU = 1,
};

enum MyActions
{
	Quit,
	Click
};


/* TEST */


struct A : public BaseComponent<A>
{
	int a;

	A(int _a) :a(_a) {}
};

struct B : public BaseComponent<B>
{
	string b;

	B(string _b) : b(_b) {}
};

struct C : public BaseComponent<C>
{
	string c;
	
	C(string _c) : c(_c) {}

	void changeb(string msg)
	{
		parent->get<B>().b = msg;
	}

};

struct AB : public Object
{
public:
	AB(int _a, string _b)
	{
		components.push_back(new A(_a));
		components.push_back(new B(_b));
	}
};

/* END TEST */


int main()
{
	/* Instance each module */
	Application<MyState, MyActions> app(800, 600, "Cosmic Colliders");
	Graphics graphics;
	// AI
	// Physics


	/* TESTING ACTIONS AND SPRITES */


	app.amap[Quit] = (Action(sf::Event::Closed) || Action(sf::Keyboard::Escape, Action::ReleaseOnce));
	app.amap[Click] = (Action(sf::Mouse::Left, Action::PressOnce));

	app.changeState(MAIN_MENU);
	app.window.setFramerateLimit(20);

	/* Sprites only store pointers to the texture, so in order to get anything to show up, you have to use the .get() after calling load() */
	MyBox box(graphics.load("box.png").get());

	cout << graphics.sprites.size() << endl;

	box.pos.x = (app.window.getSize().x / 2);
	box.pos.y = (app.window.getSize().y / 2);

	box.sprite.setPosition(box.pos);

	/* END SPRITES */


	/* TESTING ENTITIES */

	AB ab(5, "did it work?");
	cout << "a: "		 << ab.get<A>().a << endl;
	cout << "a's type: " << ab.get<A>().getType() << endl;

	cout << "b: "		 << ab.get<B>().b << endl;
	cout << "b's type: " << ab.get<B>().getType() << endl;

	cout << "Is there a C element?" << endl;

	if (ab.hasPart<C>())
		cout << "Yes." << endl;
	else
		cout << "No." << endl;

	ab.addPart(new C("It worked!! :D"));

	cout << "How about now?" << endl;

	if (ab.hasPart<C>())
	{
		cout << "Yes, value: " << ab.get<C>().c << endl;
		cout << "Type: " << ab.get<C>().getType() << endl;


		cout << "Changing b's value through C" << endl;
		ab.get<C>().changeb("This is amazing.");

		cout << "b: " << ab.get<B>().b << endl;

	}
	else
	{
		cout << "No. :(" << endl;
	}

	/* END ENTITIES */

	/* Main loop */

	while (app.window.isOpen())
	{

		switch (app.getState())
		{
		
		case MAIN_MENU:

			/* Updates the action map */
			app.amap.update(app.window);

			if (app.amap.isActive(Quit))
			{
				cout << "Quitting" << endl;
				app.quit();
			}

			if (app.amap.isActive(Click))
			{
				cout << "Clicked at (" << sf::Mouse::getPosition(app.window).x << ", " << sf::Mouse::getPosition(app.window).y << ")" << endl;
				box.sprite.move(-5, -6);

			}

			break;
		default:
			cout << "I don't know what happened, I'm out" << endl;
			app.quit();
			break;
		}


		app.window.clear(sf::Color::Black);
		app.window.draw(box.sprite);
		app.window.display();


	}

	return 0;
}