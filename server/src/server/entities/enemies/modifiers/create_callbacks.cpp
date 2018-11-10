#include <sanguis/server/entities/enemies/modifiers/agile.hpp>
#include <sanguis/server/entities/enemies/modifiers/armored.hpp>
#include <sanguis/server/entities/enemies/modifiers/burning.hpp>
#include <sanguis/server/entities/enemies/modifiers/container.hpp>
#include <sanguis/server/entities/enemies/modifiers/create_callbacks.hpp>
#include <sanguis/server/entities/enemies/modifiers/fast.hpp>
#include <sanguis/server/entities/enemies/modifiers/freezing.hpp>
#include <sanguis/server/entities/enemies/modifiers/health.hpp>
#include <sanguis/server/entities/enemies/modifiers/regenerating.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)
FCPPT_PP_DISABLE_CLANG_WARNING(-Wexit-time-destructors)

sanguis::server::entities::enemies::modifiers::container const callbacks{
	&sanguis::server::entities::enemies::modifiers::agile,
	&sanguis::server::entities::enemies::modifiers::armored,
	&sanguis::server::entities::enemies::modifiers::burning,
	&sanguis::server::entities::enemies::modifiers::fast,
	&sanguis::server::entities::enemies::modifiers::freezing,
	&sanguis::server::entities::enemies::modifiers::health,
	&sanguis::server::entities::enemies::modifiers::regenerating
};

FCPPT_PP_POP_WARNING

}

sanguis::server::entities::enemies::modifiers::container const &
sanguis::server::entities::enemies::modifiers::create_callbacks()
{
	return
		callbacks;
}
