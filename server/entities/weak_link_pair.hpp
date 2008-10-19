#ifndef SANGUIS_SERVER_ENTITIES_WEAK_LINK_PAIR_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WEAK_LINK_PAIR_HPP_INCLUDED

namespace sanguis
{
namespace server
{
namespace entities
{

class entity;

class weak_link_pair {
	weak_link_pair(
		entity *,
		entity *);
	
	entity *me,
	       *ref;
	
	void swap(
		weak_link_pair &);

	friend class auto_weak_link;
};

}
}
}

#endif
