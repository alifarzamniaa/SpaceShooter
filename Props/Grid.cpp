#include "Grid.h"
#include <iostream>

Grid::Grid(int wCell, int hCell, sf::RenderWindow& window)
	:
	cellWidth(wCell),
	cellHeight(hCell)
{
	GridSizeX = window.getSize().x / cellWidth;
	GridSizeY = window.getSize().y / cellHeight;
	GridSystem.resize(GridSizeX);
	for(auto& g : GridSystem)
		g.resize(GridSizeY);

	//we dont want to resize the array of entities because it will be filled with AddToGrid later
}

void Grid::AddToGrid(Entity* e)
{
	if(e)
	{
		auto EntityLastOccupied = e->GetLastOccupied();
		NewOccupied.clear();
		//Looping through cells that an entity occupies
		int left = (e->GetPosition().x - (e->GetSize().x / 2)) / GetCellWidth();
		int right = (e->GetPosition().x + (e->GetSize().x / 2)) / GetCellWidth();
		int top = (e->GetPosition().y - (e->GetSize().y / 2)) / GetCellHeight();
		int bottom = (e->GetPosition().y + (e->GetSize().y / 2)) / GetCellHeight();
		for(int i = left; i <= right;i++)
		{
			for(int j = top;j <= bottom;j++)
			{
				//making sure we do not check outside the screen entities
				if (i < GetGridSizeX() && j < GetGridSizeY() && i >= 0 && j >= 0)
				{
					// if it is not already in the grid
					if(std::find(GridSystem[i][j].begin(), GridSystem[i][j].end(), e) == GridSystem[i][j].end())
					{
						GridSystem[i][j].push_back(e);
						NewOccupied.insert({ i,j });
					}
				}
			}
		}
		if(!NewOccupied.empty())
		{
			RemoveGrid(EntityLastOccupied, e);
			e->SetOccupied(EntityLastOccupied);
		}
		
	}
}

void Grid::RemoveGrid(std::vector<sf::Vector2i>& oldCells, Entity* e)
{
	for (auto& cell : oldCells)
	{
		auto it = NewOccupied.find(cell);
		//if we don't find the position of the new grid
		if (it == NewOccupied.end())
		{
			//finding the entity at the old grid 
			auto eIt = std::find(GridSystem[cell.x][cell.y].begin(), GridSystem[cell.x][cell.y].end(), e);
			GridSystem[cell.x][cell.y].erase(eIt);
		}
	}
	oldCells.clear();
	for (auto& cell : NewOccupied)
	{
		// updating the old grid to new cell
		oldCells.push_back(cell);
	}
}
std::vector<Entity*> Grid::GetFromGrid(int wCell, int hCell) const
{
	if (wCell < GetGridSizeX() && hCell < GetGridSizeY() && wCell >= 0 && hCell >= 0)
		return GridSystem[wCell][hCell];
}

std::vector<Entity*> Grid::GetFromGrid(const sf::Vector2f& Pos) const
{
	int x = Pos.x / GetCellWidth();
	int y = Pos.y / GetCellHeight();
	if(x < GetGridSizeX() && y < GetGridSizeY() && x >= 0 && y >= 0)
		return GridSystem[x][y];
}

bool Grid::IsEntityCollides(Entity& e)
{
	int left = (e.GetPosition().x - (e.GetSize().x / 2)) / GetCellWidth();
	int right = (e.GetPosition().x + (e.GetSize().x / 2)) / GetCellWidth();
	int top = (e.GetPosition().y - (e.GetSize().y / 2)) / GetCellHeight();
	int bottom = (e.GetPosition().y + (e.GetSize().y / 2)) / GetCellHeight();

	for (int i = left; i <= right; i++)
	{
		for (int j = top; j <= bottom; j++)
		{
			if (i < GetGridSizeX() && j < GetGridSizeY() && i >= 0 && j >= 0)
			{
				if (!GridSystem[i][j].empty())
				{
					for (int k = 0; k < GridSystem[i][j].size(); k++)
					{
						//not collding with self and self bullet
						if (GridSystem[i][j][k] != &e && e.GetTag() != GridSystem[i][j][k]->GetTag())
						{
							//add two colliding entities into the collision list if they are not already in it
							// this indicates that these two entities has already been colliding
							std::pair<Entity*,Entity*> pair = std::make_pair(&e, GridSystem[i][j][k]);
							if(CollisionCheck.find(pair) == CollisionCheck.end())
							{
								CollisionCheck.insert(pair);
								return true;
							}
						}
					}
				}
			}
		}
	}
	return false;
}

int Grid::GetCellWidth() const
{
	return cellWidth;
}

int Grid::GetCellHeight() const
{
	return cellHeight;
}

int Grid::GetGridSizeX() const
{
	return GridSizeX;
}

int Grid::GetGridSizeY() const
{
	return GridSizeY;
}

void Grid::ResetCollisionCheck()
{
	CollisionCheck.clear();
}

