#include <sanguis/server/radius.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/auras/slow_create.hpp>
#include <sanguis/server/buffs/slow.hpp>
#include <sanguis/server/buffs/slow_factor.hpp>
#include <sanguis/server/entities/enemies/attribute.hpp>
#include <sanguis/server/entities/enemies/parameters.hpp>
#include <sanguis/server/entities/enemies/modifiers/freezing.hpp>
#include <sanguis/server/entities/enemies/modifiers/parameters_fwd.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>


sanguis::server::entities::enemies::attribute
sanguis::server::entities::enemies::modifiers::freezing(
	fcppt::reference<
		sanguis::server::entities::enemies::parameters
	> const _parameters,
	sanguis::server::entities::enemies::modifiers::parameters const &
)
{
	_parameters->add_aura(
		sanguis::server::auras::slow_create<
			sanguis::server::buffs::slow
		>(
			sanguis::server::radius(
				200.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
			),
			sanguis::server::team::monsters,
			sanguis::server::buffs::slow_factor(
				0.3F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
			)
		)
	);

	return
		sanguis::server::entities::enemies::attribute(
			FCPPT_TEXT("freezing")
		);
}
