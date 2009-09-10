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
		if(
			it->expired()
		)
			next
				= entries_.erase(
					it
				);
		else
			++next;
	}
}

