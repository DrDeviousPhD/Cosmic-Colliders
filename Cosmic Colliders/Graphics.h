#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <Thor\Resources.hpp>

#include <vector>
#include <string>
using namespace std;

struct Graphics
{
	thor::MultiResourceCache cache;
	
	/* I guess we'll use a vector for now..? */
	vector<shared_ptr<sf::Texture>> sprites;
	
	shared_ptr<sf::Texture> load(string filename)
	{
		cout << "Adding " << filename << " to list of sprites." << endl;
		sprites.push_back(cache.acquire(thor::Resources::fromFile<sf::Texture>(filename)));
		return sprites.back();
	}
};

#endif