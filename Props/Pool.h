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
		pool.resize(size);
	}
	Entity* GetFreeEntity()
	{
		auto poolIt = std::find_if(pool.begin(),pool.end(),[](const Entity& e)
		{
			return e.IsActive();
		});
		if(poolIt != pool.end())
			return poolIt->get();
		else
			return nullptr;
	}
	void AddEntity(std::unique_ptr<Entity> e)
	{
		pool.push_back(std::move(e));
	}
	int GetSize() const { return size; }
private:
	std::vector<std::unique_ptr<Entity>> pool;
	int size;
};

