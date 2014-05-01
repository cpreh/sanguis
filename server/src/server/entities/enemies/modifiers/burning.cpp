#include <sanguis/duration_second.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/auras/burn_create.hpp>
#include <sanguis/server/buffs/burn.hpp>
#include <sanguis/server/buffs/burn_interval.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/entities/enemies/attribute.hpp>
#include <sanguis/server/entities/enemies/parameters.hpp>
#include <sanguis/server/entities/enemies/modifiers/burning.hpp>
#include <sanguis/server/entities/enemies/modifiers/parameters_fwd.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::enemies::attribute
sanguis::server::entities::enemies::modifiers::burning(
	sanguis::server::entities::enemies::parameters &_parameters,
	sanguis::server::entities::enemies::modifiers::parameters const &
)
{
	_parameters.add_aura(
		sanguis::server::auras::burn_create<
			sanguis::server::buffs::burn
		>(
			sanguis::server::radius(
				400.f
			),
			sanguis::server::team::monsters,
			sanguis::server::buffs::burn_interval(
				sanguis::duration_second(
					1.f
				)
			),
			sanguis::server::damage::unit(
				1.f
				*
				std::sqrt(
					_parameters.difficulty().get()
				)
			)
		)
	);

	return
		sanguis::server::entities::enemies::attribute(
			FCPPT_TEXT("burning")
		);
}
