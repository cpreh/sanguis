#include "aggro.hpp"
#include <fcppt/assign/make_container.hpp>

sanguis::server::auras::aggro::aggro(
	space_unit const _radius,
	team::type const _team,
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
{}

void
sanguis::server::auras::aggro::enter(
	entities::base &_target
)
{
	add_target_(
		_target
	);
}

void
sanguis::server::auras::aggro::leave(
	entities::base &_target
)
{
	remove_target_(
		_target
	);
}
