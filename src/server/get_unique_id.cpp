#include "get_unique_id.hpp"

sanguis::entity_id sanguis::server::get_unique_id()
{
	static entity_id id = 0;
	return static_cast<entity_id>(id++);
}
