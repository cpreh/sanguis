#ifndef SANGUIS_SERVER_WORLD_SIGHT_RANGE_ENTRY_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_SIGHT_RANGE_ENTRY_HPP_INCLUDED

#include "sight_range_entry_fwd.hpp"
#include "../../entity_id.hpp"
#include "../../time_type.hpp"

namespace sanguis
{
namespace server
{
namespace world
{

class sight_range_entry {
public:
	sight_range_entry(
		entity_id,
		time_type
	);

	void
	update(
		time_type
	);

	entity_id
	id() const;

	bool
	expired() const;
private:
	entity_id id_;
	time_type last_time_;
};

}
}
}

#endif
