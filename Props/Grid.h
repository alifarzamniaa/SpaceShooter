#pragma once
#include <vector>
#include "../Entity.h"
#include "SFML/Graphics.hpp"
#include <unordered_set>
#include <functional>
struct EntityBoundry
{
	float left;
	float right;
	float top;
	float bottom;
};
struct CellEntityInfo
{
	int id;
	sf::Vector2f Position;
	sf::Vector2f Size;
	Type EntityType;

	bool operator==(const CellEntityInfo& other)
	{
		return id == other.id;
	}
};
struct Vec2Hash
{	
	std::size_t operator()(const sf::Vector2i& vec) const
	{
		std::size_t hashX = std::hash<int>()(vec.x);
		std::size_t hashY = std::hash<int>()(vec.y);
		return hashX ^ (hashY << 1);
	}
};
class Grid
{
public:
	Grid(int wCell,int hCell,sf::RenderWindow& window);
	void AddToGrid(const CellEntityInfo& eInfo);
	void RemoveFromGrid(const CellEntityInfo& eInfo);
	bool IsEntityCollides(CellEntityInfo& eInfo);
	std::vector<CellEntityInfo> GetCollidedEntites(const CellEntityInfo& eInfo);
	EntityBoundry GetBoundary(const CellEntityInfo& eInfo);
	int GetCellWidth() const;
	int GetCellHeight() const;
	int GetGridSizeX() const;
	int GetGridSizeY() const;
private:
	void RemoveOldGrid(const CellEntityInfo& eInfo);
	int IndexAccess(int x,int y) const;
private:
	//(NOTE) GridSystem is a 1D array of grid cells (flattened from 2D using index = GridSizeX (the width) * x + y)
	// each cell contains a vector of entities (CellEntityInfo) overlapping that cell.
	std::vector<std::vector<CellEntityInfo>> GridSystem;
	//std::unordered_set<sf::Vector2i,Vec2iHash> NewOccupied;
	std::unordered_set<sf::Vector2i,Vec2Hash> NewOccupied;
	std::unordered_map<int,std::vector<sf::Vector2i>> PrevPositions;
	int GridSizeX;
	int GridSizeY;
	int cellWidth;
	int cellHeight;
	
};