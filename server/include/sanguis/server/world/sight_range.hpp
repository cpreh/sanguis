#ifndef SANGUIS_SERVER_WORLD_SIGHT_RANGE_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_SIGHT_RANGE_HPP_INCLUDED

#include <sanguis/entity_id.hpp>
#include <sanguis/server/world/sight_range_entry_set.hpp>
#include <sanguis/server/world/sight_range_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace world
{

class sight_range
{
public:
	sight_range();

	void
	add(
		sanguis::entity_id
	);

	void
	remove(
		sanguis::entity_id
	);

	bool
	contains(
		sanguis::entity_id
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
