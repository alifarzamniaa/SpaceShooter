#include "ItemResource.h"
#include <iostream>
ItemResource::ItemResource()
{
	if (!HealthTexture.loadFromFile("Images/Items/HP.png"))
	{
		std::cout << "FAILED TO LOAD Health ITEM TEXTURE!!!\n";
	}
	
}
