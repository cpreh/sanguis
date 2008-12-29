#include "weapon_pickup.hpp"
#include "../model.hpp"
#include "../z_ordering.hpp"
#include "../../load/weapon_pickup_name.hpp"

sanguis::draw::entity_auto_ptr
sanguis::draw::factory::weapon_pickup(
	environment const &env,
	entity_id const id,
	system &sys,
	weapon_type::type const wtype)
{
	return entity_auto_ptr(
		new model(
			env,
			id,
			sys,
			load::weapon_pickup_name(
				wtype),
			z_ordering::pickup,
			false));
}
