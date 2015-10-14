#include <sanguis/server/damage/armor_meta.hpp>
#include <sanguis/server/damage/armor_unit.hpp>
#include <sanguis/server/damage/meta.hpp>
#include <sanguis/server/damage/type.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/damage/wrapper.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


sanguis::server::damage::wrapper::wrapper(
	sanguis::server::damage::type const _type
)
:
	type_(
		_type
	)
{
}

sanguis::server::damage::meta
sanguis::server::damage::wrapper::operator=(
	sanguis::server::damage::unit const _unit
) const
{
FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)
	return
		sanguis::server::damage::meta(
			type_,
			_unit
		);
FCPPT_PP_POP_WARNING
}

sanguis::server::damage::armor_meta
sanguis::server::damage::wrapper::operator=(
	sanguis::server::damage::armor_unit const _unit
) const
{
FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)
	return
		sanguis::server::damage::armor_meta(
			type_,
			_unit
		);
FCPPT_PP_POP_WARNING
}
