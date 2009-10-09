#include "sight_range.hpp"
#include "../../exception.hpp"
#include <sge/text.hpp>

sanguis::server::world::sight_range::sight_range()
:
	entries_()
{}

void
sanguis::server::world::sight_range::add(
	entity_id const id
)
{
	if(
		!entries_.insert(
			id
		).second
	)
		throw exception(
			SGE_TEXT("Failed to insert a sight range!")
		);
}

void
sanguis::server::world::sight_range::remove(
	entity_id const id
)
{
	if(
		!entries_.erase(
			id
		)
	)
		throw exception(
			SGE_TEXT("Failed to remove a sight range!")
		);
}

bool
sanguis::server::world::sight_range::contains(
	entity_id const id
) const
{
	return
		entries_.find(
			id
		)
		!= entries_.end();
}

bool
sanguis::server::world::sight_range::empty() const
{
	return entries_.empty();
}
