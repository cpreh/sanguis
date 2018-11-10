#include <sanguis/server/damage/ice.hpp>
#include <sanguis/server/damage/type.hpp>
#include <sanguis/server/damage/wrapper.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)

sanguis::server::damage::wrapper const
sanguis::server::damage::ice(
	sanguis::server::damage::type::ice
);

FCPPT_PP_POP_WARNING
