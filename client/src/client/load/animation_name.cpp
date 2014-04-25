#include <sanguis/client/load/animation_name.hpp>
#include <sanguis/client/load/animation_type.hpp>
#include <sanguis/model/animation_name.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>


sanguis::model::animation_name
sanguis::client::load::animation_name(
	sanguis::client::load::animation_type const _type
)
{
#define SANGUIS_LOAD_ANIMATION_NAME_CASE(\
	name\
)\
case sanguis::client::load::animation_type::name:\
	return \
		sanguis::model::animation_name(\
			FCPPT_TEXT(\
				#name\
			)\
		)
	switch(
		_type
	)
	{
		SANGUIS_LOAD_ANIMATION_NAME_CASE(
			none
		);
		SANGUIS_LOAD_ANIMATION_NAME_CASE(
			attacking
		);
		SANGUIS_LOAD_ANIMATION_NAME_CASE(
			walking
		);
		SANGUIS_LOAD_ANIMATION_NAME_CASE(
			dying
		);
		SANGUIS_LOAD_ANIMATION_NAME_CASE(
			deploying
		);
		SANGUIS_LOAD_ANIMATION_NAME_CASE(
			reloading
		);
	}

	FCPPT_ASSERT_UNREACHABLE;

#undef SANGUIS_LOAD_ANIMATION_NAME_CASE
}
