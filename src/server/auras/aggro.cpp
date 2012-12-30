#include <sanguis/server/radius.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/update_target_function.hpp>
#include <sanguis/server/auras/aggro.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/influence.hpp>
#include <sanguis/server/entities/with_body_fwd.hpp>


sanguis::server::auras::aggro::aggro(
	sanguis::server::radius const _radius,
	sanguis::server::team const _team,
	sanguis::server::update_target_function const &_add_target,
	sanguis::server::update_target_function const &_remove_target
)
:
	sanguis::server::auras::aura(
		_radius,
		_team,
		sanguis::server::auras::influence::debuff
	),
	add_target_(
		_add_target
	),
	remove_target_(
		_remove_target
	)
{
}

sanguis::server::auras::aggro::~aggro()
{
}

void
sanguis::server::auras::aggro::enter(
	sanguis::server::entities::with_body &_target
)
{
	add_target_(
		_target
	);
}

void
sanguis::server::auras::aggro::leave(
	sanguis::server::entities::with_body &_target
)
{
	remove_target_(
		_target
	);
}
