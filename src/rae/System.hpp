#ifndef RAE_SYSTEM_HPP
#define RAE_SYSTEM_HPP

#include <vector>
#include "Entity.hpp"

namespace Rae
{

// interface
class System
{
public:
	System()
	{
	}

public:
	virtual void update(double time, double delta_time, std::vector<Entity>& entities) = 0;
};

}

#endif

