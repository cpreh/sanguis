#include <sanguis/server/entities/enemies/skills/factory/container.hpp>
#include <sanguis/server/entities/enemies/skills/factory/create_callbacks.hpp>
#include <sanguis/server/entities/enemies/skills/factory/mother_spider.hpp>
#include <sanguis/server/entities/enemies/skills/factory/teleport.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)
FCPPT_PP_DISABLE_CLANG_WARNING(-Wexit-time-destructors)

// NOLINTNEXTLINE(fuchsia-statically-constructed-objects,cert-err58-cpp)
sanguis::server::entities::enemies::skills::factory::container const callbacks{
	&sanguis::server::entities::enemies::skills::factory::teleport,
	&sanguis::server::entities::enemies::skills::factory::mother_spider
};

FCPPT_PP_POP_WARNING

}

sanguis::server::entities::enemies::skills::factory::container const &
sanguis::server::entities::enemies::skills::factory::create_callbacks()
{
	return
		callbacks;
}
