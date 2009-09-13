#include "sight_range_entry.hpp"

sanguis::server::world::sight_range_entry::sight_range_entry(
	entity_id const id_,
	time_type const last_time_
)
:
	id_(id_),
	last_time_(last_time_)
{}

void
sanguis::server::world::sight_range_entry::update(
	time_type const new_time_
)
{
	last_time_ = new_time_;
}

sanguis::entity_id
sanguis::server::world::sight_range_entry::id() const
{
	return id_;
}

bool
sanguis::server::world::sight_range_entry::expired(
	time_type const new_time_
) const
{
	// TODO: sge::chrono!
	return new_time_ - last_time_ > static_cast<time_type>(30);
}
