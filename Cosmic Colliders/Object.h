#ifndef OBJECT_H
#define OBJECT_H

#include <SFML\Graphics.hpp>

#include <string>
#include <vector>
using namespace std;

#include "Component.h"

/*
	Based off this: http://www.gamedev.net/page/resources/_/technical/game-programming/entities-parts-i-game-objects-r3596
	and this: http://www.reddit.com/r/learnprogramming/comments/1jzlon/cwhy_exactly_is_rtti_and_typeid_bad/cbkz2mc
*/


/*	Basically just a container for components*/
class Object
{
public:

	vector<Component*> components;

	template <typename T>
	bool hasPart()
	{
		for (auto it = components.begin(); it != components.end(); it++)
		{
			if ((*it)->getType() == T::type)
				return true;
		}
		return false;
	}

	template <typename T>
	bool addPart(T *comp)
	{
		if (hasPart<T>())
		{
			cout << "Already have a component of this type" << endl;
			return false;
		}
		else
		{
			comp->setParent(this);
			components.push_back(comp);
			return true;
		}
	}

	//template <typename T>
	//bool removePart(T *comp)
	//{}


	template <typename T> 
	T& get()
	{
		/* This has some code reuse from hasPart(), but I think that's preferable over iterating twice over the same vector if we don't actually need to */

		for (auto it = components.begin(); it != components.end(); it++)
		{
			if ((*it)->getType() == T::type)
			{
				return *static_cast<T*> (*it);
			}
		}

		throw std::invalid_argument("Could not find the component");		// I hope this works.
	}

};

#endif