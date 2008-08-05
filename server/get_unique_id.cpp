#include "get_unique_id.hpp"
#include <sge/iostream.hpp>

sanguis::entity_id sanguis::server::get_unique_id()
{
	static entity_id id = 0;
	sge::cerr << "server: adding id " << id << "\n";
	return static_cast<entity_id>(id++);
}
