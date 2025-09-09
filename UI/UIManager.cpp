#include "UIManager.h"

UIManager::UIManager(sf::RenderWindow& window, float PlayerInitHealth)
	:
	window(window),
	pHealth({0,880},PlayerInitHealth)
{
}
void UIManager::Draw()
{
	pHealth.Draw(window);
}
void UIManager::PlayerHealthChange(float Health)
{
	pHealth.onHealthChange(Health);
}