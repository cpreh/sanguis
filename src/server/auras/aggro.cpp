#include "aggro.hpp"

sanguis::server::auras::aggro::aggro(
	server::radius const _radius,
	server::team::type const _team,
	update_target_function const &_add_target,
	update_target_function const &_remove_target
)
:
	aura(
		_radius,
		_team,
		influence::debuff
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
	entities::with_body &_target
)
{
	add_target_(
		_target
	);
}

void
sanguis::server::auras::aggro::leave(
	entities::with_body &_target
)
{
	remove_target_(
		_target
	);
}
