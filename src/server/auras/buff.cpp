#include <sanguis/server/radius.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/buff.hpp>
#include <sanguis/server/auras/buff_create_callback.hpp>
#include <sanguis/server/auras/influence.hpp>
#include <sanguis/server/buffs/buff.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_buffs.hpp>


sanguis::server::auras::buff::buff(
	sanguis::server::radius const _radius,
	sanguis::server::team const _team,
	sanguis::server::auras::influence const _influence,
	sanguis::server::auras::buff_create_callback const &_buff_create_callback
)
:
	sanguis::server::auras::aura(
		_radius,
		_team,
		_influence
	),
	buff_create_callback_(
		_buff_create_callback
	),
	provider_()
{
}

sanguis::server::auras::buff::~buff()
{
}

void
sanguis::server::auras::buff::enter(
	sanguis::server::entities::with_body &_entity
)
{
	provider_.add(
		dynamic_cast<
			sanguis::server::entities::with_buffs &
		>(
			_entity
		),
		buff_create_callback_()
	);
}

void
sanguis::server::auras::buff::leave(
	sanguis::server::entities::with_body &_entity
)
{
	provider_.remove(
		dynamic_cast<
			sanguis::server::entities::with_buffs &
		>(
			_entity
		)
	);
}
