#pragma once
#include <vector>
#include "../Entity.h"
#include "SFML/Graphics.hpp"
#include <unordered_set>
#include <functional>
struct Vec2iHash
{
	std::size_t operator()(const sf::Vector2i& vec) const
	{
		std::size_t hashX = std::hash<int>()(vec.x);
		std::size_t hashY = std::hash<int>()(vec.y);
		return hashX ^ (hashY << 1);
	}
};
struct PairHash
{
	std::size_t operator()(const std::pair<Entity*,Entity*>& pair) const
	{
		std::size_t First = std::hash<Entity*>()(pair.first);
		std::size_t Second = std::hash<Entity*>()(pair.second);
		return First ^ (Second << 1);
	}
};
class Grid
{
public:
	Grid(int wCell,int hCell,sf::RenderWindow& window);
	void AddToGrid(Entity* e);
	std::vector<Entity*> GetFromGrid(int wCell,int hCell) const;
	std::vector<Entity*> GetFromGrid(const sf::Vector2f& Pos) const;
	bool IsEntityCollides(Entity& e);
	int GetCellWidth() const;
	int GetCellHeight() const;
	int GetGridSizeX() const;
	int GetGridSizeY() const;
	void ResetCollisionCheck();
private:
	void RemoveGrid(std::vector<sf::Vector2i>& oldCells,Entity* e);
private:
	std::vector<std::vector<std::vector<Entity*>>> GridSystem;
	std::unordered_set<sf::Vector2i,Vec2iHash> NewOccupied;
	std::unordered_set<std::pair<Entity*,Entity*>,PairHash> CollisionCheck;
	int GridSizeX;
	int GridSizeY;
	int cellWidth;
	int cellHeight;
};