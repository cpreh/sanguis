#include "next_id.hpp"
#include "invalid_id.hpp"

sanguis::entity_id sanguis::client::next_id()
{
	static entity_id id(invalid_id);
	return --id;
}
