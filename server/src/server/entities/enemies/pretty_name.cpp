#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/server/entities/enemies/pretty_name.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>

fcppt::string
sanguis::server::entities::enemies::pretty_name(
		sanguis::creator::enemy_type const _type
){
	switch(
			_type
		  )
	{
		case sanguis::creator::enemy_type::wolf_black:
			 return FCPPT_TEXT("Black Wolf");
		case sanguis::creator::enemy_type::wolf_brown:
			 return FCPPT_TEXT("Brown Wolf");
		case sanguis::creator::enemy_type::wolf_white:
			 return FCPPT_TEXT("White Wolf");
		case sanguis::creator::enemy_type::zombie00:
			 return FCPPT_TEXT("Shambler");
		case sanguis::creator::enemy_type::zombie01:
			 return FCPPT_TEXT("Runner");
		case sanguis::creator::enemy_type::spider:
			 return FCPPT_TEXT("Wasp Spider");
		case sanguis::creator::enemy_type::skeleton:
			 return FCPPT_TEXT("Skeleton");
		case sanguis::creator::enemy_type::ghost:
			 return FCPPT_TEXT("Ghost");
		case sanguis::creator::enemy_type::maggot:
			 return FCPPT_TEXT("Maggot");
		case sanguis::creator::enemy_type::reaper:
			 return FCPPT_TEXT("Grim Reaper");
	}
	FCPPT_ASSERT_UNREACHABLE;
}
