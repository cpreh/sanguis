#include <sanguis/exception.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/server/waves/convert_enemy_name.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>


sanguis::creator::enemy_type
sanguis::server::waves::convert_enemy_name(
	fcppt::string const &_name
)
{
#define SANGUIS_NAME_CASE(\
	name \
) \
	if(\
		_name == FCPPT_TEXT(#name)\
	)\
		return sanguis::creator::enemy_type::name;

	SANGUIS_NAME_CASE(wolf_black)
	SANGUIS_NAME_CASE(wolf_brown)
	SANGUIS_NAME_CASE(wolf_white)
	SANGUIS_NAME_CASE(zombie00)
	SANGUIS_NAME_CASE(zombie01)
	SANGUIS_NAME_CASE(spider)
	SANGUIS_NAME_CASE(skeleton)
	SANGUIS_NAME_CASE(maggot)

	throw
		sanguis::exception(
			FCPPT_TEXT("Invalid enemy name ")
			+ _name
		);
#undef SANGUIS_NAME_CASE
}
