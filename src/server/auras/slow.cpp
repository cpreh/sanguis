#include <sanguis/server/radius.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/influence.hpp>
#include <sanguis/server/auras/slow.hpp>
#include <sanguis/server/entities/with_body.hpp>


sanguis::server::auras::slow::slow(
	sanguis::server::radius const _radius,
	sanguis::server::team const _team,
	sanguis::server::auras::slow::factor const _factor
)
:
	sanguis::server::auras::aura(
		_radius,
		_team,
		sanguis::server::auras::influence::debuff
	),
	factor_(
		_factor
	),
	provider_()
{
}

sanguis::server::auras::slow::~slow()
{
}

void
sanguis::server::auras::slow::enter(
	sanguis::server::entities::with_body &_entity
)
{
/*
	provider_.add(
		dynamic_cast<
			sanguis::server::entities::with_buffs &
		>(
			_entity
		),
		sanguis::server::buffs::unique_ptr(
			fcppt::make_unique_ptr<
				sanguis::server::buffs::slow
			>(
				sanguis::server::buffs::slow::factor(
					factor_.get()
				)
			)
		)
	);*/
}

void
sanguis::server::auras::slow::leave(
	sanguis::server::entities::with_body &_entity
)
{
/*
	provider_.remove(
		dynamic_cast<
			sanguis::server::entities::with_buffs &
		>(
			_entity
		)
	);*/
}
