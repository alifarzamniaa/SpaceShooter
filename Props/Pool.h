#pragma once
#include "../Entity.h"
#include <memory>
class Pool
{
public:
	Pool(int size = 100)
		:
		size(size)
	{
	}
	// getting the first entity that is InActive so we can activate and use it
	Entity* GetFreeEntity()
	{
		auto poolIt = std::find_if(pool.begin(),pool.end(),[](const std::unique_ptr<Entity>& e)
		{
			if(e)
				return !e->IsActive();
		});
		if(poolIt != pool.end())
			return poolIt->get();
		else
			return nullptr;
	}
	// get an array of active items so we know which ones are currently available
	std::vector<Entity*> GetActiveItem()
	{
		std::vector<Entity*> items;
		for(auto& e : pool)
		{
			if(e && e->IsActive())
			{
				items.push_back(e.get());
			}
		}
		return items;
	}
	// add entity to the pool system
	// you must fill the entire array with this so you can re-use the pre created objects
	void AddEntity(std::unique_ptr<Entity> e)
	{
		pool.push_back(std::move(e));
	}
	int GetSize() const { return size; }
private:
	std::vector<std::unique_ptr<Entity>> pool;
	int size;
};

