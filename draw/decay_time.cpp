#include "decay_time.hpp"

sanguis::time_type
sanguis::draw::decay_time(
	const entity_type::type type)
{
	switch(type) {
	case entity_type::bullet:
	case entity_type::pickup:
		return static_cast<time_type>(0);
	default: // FIXME
		return static_cast<time_type>(60);
	}
}
