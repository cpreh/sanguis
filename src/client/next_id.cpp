#include "next_id.hpp"
#include <limits>

// FIXME: this should not be here!
sanguis::entity_id const
sanguis::client::next_id()
{
	static sanguis::entity_id id(
		std::numeric_limits<
			sanguis::entity_id::value_type
		>::max()
	);

	return
		--id;
}
