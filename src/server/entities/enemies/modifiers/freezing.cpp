#include <sanguis/server/radius.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/auras/slow_create.hpp>
#include <sanguis/server/buffs/slow.hpp>
#include <sanguis/server/buffs/slow_factor.hpp>
#include <sanguis/server/entities/enemies/attribute.hpp>
#include <sanguis/server/entities/enemies/parameters.hpp>
#include <sanguis/server/entities/enemies/modifiers/freezing.hpp>
#include <fcppt/text.hpp>


sanguis::server::entities::enemies::attribute
sanguis::server::entities::enemies::modifiers::freezing(
	sanguis::server::entities::enemies::parameters &_parameters
)
{
	_parameters.add_aura(
		sanguis::server::auras::slow_create<
			sanguis::server::buffs::slow
		>(
			sanguis::server::radius(
				400.f
			),
			sanguis::server::team::monsters,
			sanguis::server::buffs::slow_factor(
				0.3f
			)
		)
	);

	return
		sanguis::server::entities::enemies::attribute(
			FCPPT_TEXT("freezing")
		);
}
