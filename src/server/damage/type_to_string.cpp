#include <sanguis/server/damage/type.hpp>
#include <sanguis/server/damage/type_to_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>


fcppt::string
sanguis::server::damage::type_to_string(
	sanguis::server::damage::type const _type
)
{
	#define SANGUIS_SERVER_DAMAGE_TYPE_TO_STRING_CASE(\
		name\
	)\
	case sanguis::server::damage::type::name:\
		return \
			FCPPT_TEXT(\
				#name\
			)

	switch(
		_type
	)
	{
		SANGUIS_SERVER_DAMAGE_TYPE_TO_STRING_CASE(
			normal
		);
		SANGUIS_SERVER_DAMAGE_TYPE_TO_STRING_CASE(
			piercing
		);
		SANGUIS_SERVER_DAMAGE_TYPE_TO_STRING_CASE(
			fire
		);
		SANGUIS_SERVER_DAMAGE_TYPE_TO_STRING_CASE(
			ice
		);
		SANGUIS_SERVER_DAMAGE_TYPE_TO_STRING_CASE(
			pure
		);
	}

	FCPPT_ASSERT_UNREACHABLE;

	#undef SANGUIS_SERVER_DAMAGE_TYPE_TO_STRING_CASE
}
