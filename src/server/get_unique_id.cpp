#include <sanguis/server/get_unique_id.hpp>

sanguis::entity_id const
sanguis::server::get_unique_id()
{
	// TODO: this should not bere here!
	static sanguis::entity_id id(
		0u
	);

	return id++;
}
