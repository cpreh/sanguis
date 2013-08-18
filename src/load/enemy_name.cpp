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
#define SANGUIS_LOAD_ENEMY_NAME_CASE(\
	name\
)\
case sanguis::creator::enemy_type::name:\
	return \
		FCPPT_TEXT(\
			#name\
		)
	switch(
		_type
	)
	{
		SANGUIS_LOAD_ENEMY_NAME_CASE(
			wolf_black
		);
		SANGUIS_LOAD_ENEMY_NAME_CASE(
			wolf_brown
		);
		SANGUIS_LOAD_ENEMY_NAME_CASE(
			wolf_white
		);
		SANGUIS_LOAD_ENEMY_NAME_CASE(
			zombie00
		);
		SANGUIS_LOAD_ENEMY_NAME_CASE(
			zombie01
		);
		SANGUIS_LOAD_ENEMY_NAME_CASE(
			spider
		);
		SANGUIS_LOAD_ENEMY_NAME_CASE(
			skeleton
		);
		SANGUIS_LOAD_ENEMY_NAME_CASE(
			maggot
		);
	}

	FCPPT_ASSERT_UNREACHABLE;

#undef SANGUIS_LOAD_ENEMY_NAME_CASE
}
