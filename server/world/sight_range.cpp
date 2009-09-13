#include "sight_range.hpp"

void
sanguis::server::world::sight_range::update(
	time_type const time_
)
{
	for(
		sight_range_entry_set::iterator it(
			entries_.begin()
		),
		next(it);
		it != entries_.end();
		it = next
	)
	{
		++next;

		if(
			it->expired()
		)
			entries_.erase(
				it
			);
	}
}

bool
sanguis::server::world::sight_range::add(
	entity_id const id
)
{
	/*
	entries_.insert(
		sight_range_entry(
			id,
			0 // FIXME
		)
	);
	*/
}

bool
sanguis::server::world::sight_range::contains(
	entity_id const id
) const
{
	/*
	return
		entries_.find(
			id
		)
		!= entries.end();
	*/
}
