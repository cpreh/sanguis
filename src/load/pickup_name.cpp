#include <sanguis/load/pickup_name.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/text.hpp>

fcppt::string const
sanguis::load::pickup_name(
	pickup_type::type const _type
)
{
	switch(
		_type
	)
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

	FCPPT_ASSERT_UNREACHABLE
}
