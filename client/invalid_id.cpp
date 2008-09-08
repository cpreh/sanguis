#include "invalid_id.hpp"
#include <limits>

sanguis::entity_id const
sanguis::client::invalid_id(
	std::numeric_limits<sanguis::entity_id>::max());
