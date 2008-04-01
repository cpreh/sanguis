#include "next_id.hpp"
#include <limits>

sanguis::entity_id sanguis::client::next_id()
{
	static entity_id id(std::numeric_limits<entity_id>::max());
	return id--;
}
