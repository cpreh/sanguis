#include "pickup_name.hpp"
#include "../exception.hpp"
#include <fcppt/text.hpp>

fcppt::string const
sanguis::load::pickup_name(
	pickup_type::type const ptype
)
{
	switch(ptype)
	{
	case pickup_type::health:
		return fcppt::string(
			FCPPT_TEXT("pickups/hp")
		);
	case pickup_type::monster:
		return fcppt::string(
			FCPPT_TEXT("pickups/monster")
		);
	case pickup_type::weapon:
	case pickup_type::size:
		break;
	}

	throw exception(
		FCPPT_TEXT("load::pickup_name: missing loading code!")
	);
}
