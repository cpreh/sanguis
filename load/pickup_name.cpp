#include "pickup_name.hpp"
#include "../exception.hpp"
#include <fcppt/text.hpp>

sge::string const
sanguis::load::pickup_name(
	pickup_type::type const ptype)
{
	switch(ptype) {
	case pickup_type::health:
		return sge::string(
			FCPPT_TEXT("pickups/hp")
		);
	case pickup_type::monster:
		return sge::string(
			FCPPT_TEXT("pickups/monster")
		);
	default:
		throw exception(
			FCPPT_TEXT("load::pickup_name: missing loading code!")
		);
	}
}
