#ifndef SANGUIS_SERVER_WORLD_SIGHT_RANGE_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_SIGHT_RANGE_HPP_INCLUDED

#include "sight_range_fwd.hpp"
#include "sight_range_entry_set.hpp"

namespace sanguis
{
namespace server
{
namespace world
{

class sight_range {
public:
	sight_range();

	void	
	add(
		entity_id
	);

	void
	remove(
		entity_id
	);

	bool
	contains(
		entity_id
	) const;

	bool
	empty() const;
private:
	sight_range_entry_set entries_;
};

}
}
}

#endif
