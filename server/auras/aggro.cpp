#include "aggro.hpp"
#include <sge/assign/make_container.hpp>

sanguis::server::auras::aggro::aggro(
	space_unit const radius_,
	team::type const team_,
	update_target_function const &add_target_,
	update_target_function const &remove_target_
)
:
	aura(
		radius_,
		team_,
		influence::debuff
	),
	add_target_(
		add_target_
	),
	remove_target_(
		remove_target_
	)
{}


sanguis::server::collision::group_vector const
sanguis::server::auras::aggro::collision_groups() const
{
	return 
		sge::assign::make_container<
			collision::group_vector
		>(
			collision::group::aggro_aura
		);
}

void
sanguis::server::auras::aggro::enter(
	entities::base &target
)
{
	add_target_(
		target
	);
}

void
sanguis::server::auras::aggro::leave(
	entities::base &target
)
{
	remove_target_(
		target
	);
}
