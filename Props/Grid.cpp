#include "Grid.h"
#include <iostream>

Grid::Grid(int wCell, int hCell, sf::RenderWindow& window)
	:
	cellWidth(wCell),
	cellHeight(hCell)
{
	GridSizeX = window.getSize().x / cellWidth;
	GridSizeY = window.getSize().y / cellHeight;
	GridSystem.resize(GridSizeX * GridSizeY);

	//(NOTE)we dont want to resize the array of entities (CellEntityInfo array) because it will be filled with AddToGrid later
}

void Grid::AddToGrid(const CellEntityInfo& eInfo)
{
		EntityBoundry eBoundry = GetBoundary(eInfo);
		NewOccupied.clear();
		for(int i = eBoundry.left; i <= eBoundry.right;i++)
		{
			for(int j = eBoundry.top;j <= eBoundry.bottom;j++)
			{
				//making sure we do not check outside the screen entities
				if (i < GetGridSizeX() && j < GetGridSizeY() && i >= 0 && j >= 0)
				{
					// if it is not already in the grid
					if(std::find(GridSystem[IndexAccess(i,j)].begin(), GridSystem[IndexAccess(i,j)].end(), eInfo) == GridSystem[IndexAccess(i,j)].end())
					{
						GridSystem[IndexAccess(i,j)].push_back(eInfo);
					}
					NewOccupied.insert({ i,j });
				}
			}
		}
		RemoveOldGrid(eInfo);
}

void Grid::RemoveFromGrid(const CellEntityInfo& eInfo)
{
	auto EntityPos = PrevPositions.find(eInfo.id);
	if (EntityPos != PrevPositions.end())
	{
		for (auto& pCell : EntityPos->second)
		{
			auto& cell = GridSystem[IndexAccess(pCell.x,pCell.y)];
			auto eIt = std::find(cell.begin(), cell.end(), eInfo);
			if (eIt != cell.end())
			{
				*eIt = cell.back(); //overwrite the current one by last element(swaping it)
				cell.pop_back();
			}
		}
		PrevPositions.erase(eInfo.id);
	}

}
void Grid::RemoveOldGrid(const CellEntityInfo& eInfo)
{
	auto EntityPos = PrevPositions.find(eInfo.id);
	if(EntityPos != PrevPositions.end())
	{
		int i = 0;
		int j = 0;
		bool ChangeHappend = false;
		auto pCell = EntityPos->second;
		for(const auto& p : pCell)
		{
			if (NewOccupied.find(p) == NewOccupied.end())
			{
					auto& cell = GridSystem[IndexAccess(p.x, p.y)];
					//finding the entity at the old grid 
					auto eIt = std::find(cell.begin(), cell.end(), eInfo);
					if (eIt != cell.end())
					{
						*eIt = cell.back(); //overwrite the current one by last element(swaping it)
						cell.pop_back();
					}
					ChangeHappend = true;
				}
				i++;
				j++;
		}
		EntityPos->second.clear();
		for (auto& nCell : NewOccupied)
		{
			// updating the old grid to new cell
			EntityPos->second.push_back(nCell);
		}
	}else
	{
		std::vector<sf::Vector2i> Pos;
		for (auto& nCell : NewOccupied)
		{
			Pos.push_back(nCell);
		}
		PrevPositions.insert({eInfo.id,Pos});
	}
	
}
int Grid::IndexAccess(int x, int y) const
{
	return y * GridSizeX + x;
}

bool Grid::IsEntityCollides(CellEntityInfo& eInfo)
{
	EntityBoundry eBoundry = GetBoundary(eInfo);

	for (int i = eBoundry.left; i <= eBoundry.right; i++)
	{
		for (int j = eBoundry.top; j <= eBoundry.bottom; j++)
		{
			if (i < GetGridSizeX() && j < GetGridSizeY() && i >= 0 && j >= 0)
			{
				if (!GridSystem[IndexAccess(i,j)].empty())
				{
					for (int k = 0; k < GridSystem[IndexAccess(i,j)].size(); k++)
					{
						//not collding with self and self bullet
						if (GridSystem[IndexAccess(i,j)][k].id != eInfo.id && eInfo.EntityType != GridSystem[IndexAccess(i,j)][k].EntityType)
						{
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

std::vector<CellEntityInfo> Grid::GetCollidedEntites(const CellEntityInfo& eInfo)
{
	EntityBoundry eBoundry = GetBoundary(eInfo);
	std::vector<CellEntityInfo> HitRes;
	for (int i = eBoundry.left; i <= eBoundry.right; i++)
	{
		for (int j = eBoundry.top; j <= eBoundry.bottom; j++)
		{
			if (i < GetGridSizeX() && j < GetGridSizeY() && i >= 0 && j >= 0)
			{
				if (!GridSystem[IndexAccess(i, j)].empty())
				{
					for(const auto& e : GridSystem[IndexAccess(i, j)])
						HitRes.push_back(e);
				}
			}
		}
	}
	return HitRes;
}

EntityBoundry Grid::GetBoundary(const CellEntityInfo& eInfo)
{
	EntityBoundry etb  = {};
	etb.left = (eInfo.Position.x - (eInfo.Size.x / 2.f)) / GetCellWidth();
	etb.right = (eInfo.Position.x + (eInfo.Size.x / 2.f)) / GetCellWidth();
	etb.top = (eInfo.Position.y - (eInfo.Size.y / 2.f)) / GetCellHeight();
	etb.bottom = (eInfo.Position.y + (eInfo.Size.y / 2.f)) / GetCellHeight();
	return etb;
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

