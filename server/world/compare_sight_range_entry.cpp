#include "compare_sight_range_entry.hpp"
#include "sight_range_entry.hpp"

bool
sanguis::server::world::compare_sight_range_entry(
	sight_range_entry const &a,
	sight_range_entry const &b
)
{
	return a.id() < b.id();
}
