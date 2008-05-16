#include "freeze.hpp"

sanguis::server::entities::auras::freeze::freeze(
	environment const &env,
	messages::pos_type const &pos,
	const messages::space_unit radius,
	const team::type team)
: aura(
	env,
	pos,
	radius,
	team)
{}

void sanguis::server::entities::auras::freeze::do_effect(
	entity &target)
{
	target.get_property(
		property::type::movement_speed).max(
			messages::mu(0));
	target.get_property(
		property::type::attack_speed).max(
			messages::mu(0));
}
