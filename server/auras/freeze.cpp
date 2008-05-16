#include "freeze.hpp"
#include "../entities/entity.hpp"
#include "../entities/property.hpp"

sanguis::server::auras::freeze::freeze(
	messages::circle_type const &circle_,
	const team::type team,
	const influence::type influence_)
: aura(
	circle_,
	team,
	influence_)
{}

void sanguis::server::auras::freeze::do_effect(
	entities::entity &target)
{
	target.get_property(
		entities::property::type::movement_speed).max(
			messages::mu(0));
	target.get_property(
		entities::property::type::attack_speed).max(
			messages::mu(0));
}
