#ifndef RAE_3D_ENTITY_HPP
#define RAE_3D_ENTITY_HPP

#include <vector>

namespace Rae
{

struct ComponentIndex
{
public:
	ComponentIndex(int set_type, int set_id)
	: type(set_type),
	id(set_id)
	{
	}

	bool operator==(ComponentIndex& other)
	{
		if(other.type == type && other.id == id)
			return true;
		return false;
	}

	//Components are identified with 1. component type index, 2. component id index
	int type;
	int id;
};

class Entity
{
public:
	int id() { return m_id; }
protected:
	void id(int set) { m_id = set; }
	int m_id;

public:
	Entity(int set_id);
	~Entity();

	void addComponent(int set_type, int set_id)
	{
		m_components.emplace_back(set_type, set_id);
	}

	//const 
	std::vector<ComponentIndex>& components() { return m_components; }

protected:	
	std::vector<ComponentIndex> m_components;
};

}//end namespace Rae

#endif
