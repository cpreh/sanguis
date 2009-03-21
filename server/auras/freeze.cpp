#include "freeze.hpp"
#include "../entities/entity.hpp"
#include "../entities/property.hpp"

sanguis::server::auras::freeze::freeze(
	environment const &env,
	circle_type const &circle_,
	team::type const team)
:
	aura(
		env,
		circle_,
		team,
		influence::debuff
	)
{}

void sanguis::server::auras::freeze::do_effect(
	entities::entity &target)
{
	target.property(
		entities::property_type::movement_speed).max(
			messages::mu(0));
	target.property(
		entities::property_type::attack_speed).max(
			messages::mu(0));
}
