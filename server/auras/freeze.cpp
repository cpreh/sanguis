#include "freeze.hpp"
#include "../entities/entity.hpp"
#include "../entities/property.hpp"

sanguis::server::auras::freeze::freeze(
	messages::circle_type const &circle_,
	team::type const team)
: aura(
	circle_,
	team,
	influence::debuff)
{}

void sanguis::server::auras::freeze::do_effect(
	entities::entity &target)
{
	target.property(
		entities::property::type::movement_speed).max(
			messages::mu(0));
	target.property(
		entities::property::type::attack_speed).max(
			messages::mu(0));
}
