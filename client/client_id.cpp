#include "client_id.hpp"
#include <iostream>
#include <limits>

sanguis::entity_id sanguis::client::next_client_id()
{
	static entity_id id(std::numeric_limits<entity_id>::max());
	std::cout << "assigning id: " << id << "\n";
	return id--;
}
