#ifndef COMPONENT_H
#define COMPONENT_H

#include "Object.h"


/*

	How to make components:

		Components are designed using the Componenet-Entity system, with Objects using the Curiously Recurring Template Pattern.
		I thought this would be a little more effecient than using RTTI. Using CRTP means you have to define components in a particular way.
		Your class must inherit from "BaseComponent", and pass itself along as the template parameter for it. Like this:

		class MyNewComponent : public BaseComponent<MyObject>;

*/

class Object;

template<typename T>
class BaseComponent : public Component
{
public:
	
	Object *parent;
	static int type;

	/* Assumes T has a type variable? If you don't use CRTP here, will it fail on compile? */
	int getType() const { return T::type;  }

	void setParent(Object *obj) { parent = obj; }
};

/* Global, but fuck it at this point */
static int nextType = 0;
template <typename T> int BaseComponent<T>::type(nextType++);


class Component
{
public:

	virtual int getType() const = 0;

};

#endif