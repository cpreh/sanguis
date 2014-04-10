#include <sanguis/entity_id.hpp>
#include <sanguis/server/world/sight_range.hpp>
#include <fcppt/assert/error.hpp>


sanguis::server::world::sight_range::sight_range()
:
	entries_()
{
}

void
sanguis::server::world::sight_range::add(
	sanguis::entity_id const _id
)
{
	FCPPT_ASSERT_ERROR(
		entries_.insert(
			_id
		).second
	);
}

void
sanguis::server::world::sight_range::remove(
	sanguis::entity_id const _id
)
{
	FCPPT_ASSERT_ERROR(
		entries_.erase(
			_id
		)
		> 0
	);
}

bool
sanguis::server::world::sight_range::contains(
	sanguis::entity_id const _id
) const
{
	return
		entries_.find(
			_id
		)
		!=
		entries_.end();
}

bool
sanguis::server::world::sight_range::empty() const
{
	return
		entries_.empty();
}
