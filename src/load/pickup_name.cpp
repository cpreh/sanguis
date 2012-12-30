#include <sanguis/pickup_type.hpp>
#include <sanguis/load/pickup_name.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>


fcppt::string const
sanguis::load::pickup_name(
	sanguis::pickup_type const _type
)
{
	switch(
		_type
	)
	{
	case sanguis::pickup_type::health:
		return fcppt::string(
			FCPPT_TEXT("pickups/hp")
		);
	case sanguis::pickup_type::monster:
		return fcppt::string(
			FCPPT_TEXT("pickups/monster")
		);
	case sanguis::pickup_type::weapon:
	case sanguis::pickup_type::size:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
