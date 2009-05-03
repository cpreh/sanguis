#include "pickup_name.hpp"
#include "../exception.hpp"
#include <sge/text.hpp>

sge::string const
sanguis::load::pickup_name(
	pickup_type::type const ptype)
{
	switch(ptype) {
	case pickup_type::health:
		return sge::string(
			SGE_TEXT("pickups/hp")
		);
	case pickup_type::monster:
		return sge::string(
			//SGE_TEXT("pickups/monster")
			SGE_TEXT("pickups/hp") // TODO: nille!
		);
	default:
		throw exception(
			SGE_TEXT("load::pickup_name: missing loading code!")
		);
	}
}
