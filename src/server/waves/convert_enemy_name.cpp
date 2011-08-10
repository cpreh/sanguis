#include "convert_enemy_name.hpp"
#include "../../exception.hpp"
#include <fcppt/text.hpp>

sanguis::enemy_type::type
sanguis::server::waves::convert_enemy_name(
	fcppt::string const &name
)
{
	// TODO: we really need a strong enum class that can do this!
#define SANGUIS_NAME_CASE(x) \
	if(\
		name == FCPPT_TEXT(#x)\
	)\
		return enemy_type::x;

	SANGUIS_NAME_CASE(wolf_black)
	SANGUIS_NAME_CASE(wolf_brown)
	SANGUIS_NAME_CASE(wolf_white)
	SANGUIS_NAME_CASE(zombie00)
	SANGUIS_NAME_CASE(zombie01)
	SANGUIS_NAME_CASE(spider)
	SANGUIS_NAME_CASE(skeleton)
	SANGUIS_NAME_CASE(maggot)

	throw exception(
		FCPPT_TEXT("Invalid enemy name ")
		+ name
	);
#undef SANGUIS_NAME_CASE
}
