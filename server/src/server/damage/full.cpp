#include <sanguis/server/damage/full.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)

sanguis::server::damage::unit const
sanguis::server::damage::full(
	1.f
);

FCPPT_PP_POP_WARNING
