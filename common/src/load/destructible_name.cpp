#include <sanguis/creator/destructible_type.hpp>
#include <sanguis/load/destructible_name.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>


fcppt::string
sanguis::load::destructible_name(
	sanguis::creator::destructible_type const _type
)
{
	switch(
		_type
	)
	{
	case sanguis::creator::destructible_type::barrel:
		return fcppt::string(
			FCPPT_TEXT("barrel")
		);
	}

	FCPPT_ASSERT_UNREACHABLE;
}
