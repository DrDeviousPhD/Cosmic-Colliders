#ifndef DRAWCOMPONENT_H
#define DRAWCOMPONENT_H

#include <SFML\Graphics.hpp>

#include "Component.h"

class DrawComponent : public BaseComponent<DrawComponent>
{
public:

	// Would I store position in here, even though it would be needed by other componenets? 
	// Or in its own, seperate Position component?

	DrawComponent();
};

#endif