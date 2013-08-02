#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/load/enemy_name.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>


fcppt::string const
sanguis::load::enemy_name(
	sanguis::creator::enemy_type const _type
)
{
	switch(
		_type
	)
	{
	case sanguis::creator::enemy_type::wolf_black:
		return FCPPT_TEXT("wolf_black");
	case sanguis::creator::enemy_type::wolf_brown:
		return FCPPT_TEXT("wolf_brown");
	case sanguis::creator::enemy_type::wolf_white:
		return FCPPT_TEXT("wolf_white");
	case sanguis::creator::enemy_type::zombie00:
		return FCPPT_TEXT("zombie00");
	case sanguis::creator::enemy_type::zombie01:
		return FCPPT_TEXT("zombie01");
	case sanguis::creator::enemy_type::spider:
		return FCPPT_TEXT("spider");
	case sanguis::creator::enemy_type::skeleton:
		return FCPPT_TEXT("skeleton");
	case sanguis::creator::enemy_type::maggot:
		return FCPPT_TEXT("maggot");
	}

	FCPPT_ASSERT_UNREACHABLE;
}
