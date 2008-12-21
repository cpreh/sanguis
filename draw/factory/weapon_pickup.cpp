#include "weapon_pickup.hpp"
#include "../model.hpp"
#include "../z_ordering.hpp"
#include "../../load/weapon_pickup_name.hpp"

sanguis::draw::factory::entity_ptr
sanguis::draw::factory::weapon_pickup(
	load::context const &ctx,
	entity_id const id,
	system &sys,
	weapon_type::type const wtype)
{
	return entity_ptr(
		new model(
			ctx,
			id,
			sys,
			load::weapon_pickup_name(
				wtype),
			z_ordering::pickup,
			false));
}
