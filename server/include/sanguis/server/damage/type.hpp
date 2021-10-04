#ifndef SANGUIS_SERVER_DAMAGE_TYPE_HPP_INCLUDED
#define SANGUIS_SERVER_DAMAGE_TYPE_HPP_INCLUDED

#include <sanguis/server/damage/type_fwd.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace sanguis::server::damage
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wshadow)

enum class type
{
	normal,
	piercing,
	fire,
	ice,
	fcppt_maximum = ice
};

FCPPT_PP_POP_WARNING

}

#endif
