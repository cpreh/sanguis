#include "decay_time.hpp"

sanguis::time_type
sanguis::draw::decay_time(
	entity_type::type const type)
{
	switch(type) {
	case entity_type::projectile:
	case entity_type::pickup:
		return static_cast<time_type>(0);
	default: // FIXME
		return static_cast<time_type>(60);
	}
}
