#include "aggro.hpp"
#include <sge/assign/make_container.hpp>
#include <sge/optional_impl.hpp>

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
		influence::debuff,
		optional_groups(
			sge::assign::make_container<
				collision::group_vector
			>(
				collision::group::aggro_aura
			)
		)
	),
	add_target_(
		add_target_
	),
	remove_target_(
		remove_target_
	)
{}

void
sanguis::server::auras::aggro::enter(
	entities::entity &target
)
{
	add_target_(
		target
	);
}

void
sanguis::server::auras::aggro::leave(
	entities::entity &target
)
{
	remove_target_(
		target
	);
}
