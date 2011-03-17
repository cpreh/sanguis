#include "sight_range.hpp"
#include "../../exception.hpp"
#include <fcppt/text.hpp>

sanguis::server::world::sight_range::sight_range()
:
	entries_()
{
}

void
sanguis::server::world::sight_range::add(
	entity_id const _id
)
{
	if(
		!entries_.insert(
			_id
		).second
	)
		throw sanguis::exception(
			FCPPT_TEXT("Failed to insert a sight range!")
		);
}

void
sanguis::server::world::sight_range::remove(
	entity_id const _id
)
{
	if(
		!entries_.erase(
			_id
		)
	)
		throw sanguis::exception(
			FCPPT_TEXT("Failed to remove a sight range!")
		);
}

bool
sanguis::server::world::sight_range::contains(
	entity_id const _id
) const
{
	return
		entries_.find(
			_id
		)
		!= entries_.end();
}

bool
sanguis::server::world::sight_range::empty() const
{
	return entries_.empty();
}
