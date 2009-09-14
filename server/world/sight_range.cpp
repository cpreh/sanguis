#include "sight_range.hpp"
#include "compare_sight_range_entry.hpp"
#include <functional>

sanguis::server::world::sight_range::sight_range()
:
	entries_(
		std::ptr_fun(
			compare_sight_range_entry
		)
	)
{}

sanguis::server::world::entity_remove_vector const
sanguis::server::world::sight_range::update(
	time_type const time_
)
{
	entity_remove_vector ret;

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
			it->expired(
				time_
			)
		)
		{
			ret.push_back(
				it->id()
			);

			entries_.erase(
				it
			);
		}
	}

	return ret;
}

bool
sanguis::server::world::sight_range::add(
	entity_id const id,
	time_type const time_
)
{
	return entries_.insert(
		sight_range_entry(
			id,
			time_
		)
	).second;
}

bool
sanguis::server::world::sight_range::contains(
	entity_id const id
) const
{
	return
		entries_.find(
			sight_range_entry(
				id,
				static_cast<
					time_type
				>(
					0
				)
			)
		)
		!= entries_.end();
}
