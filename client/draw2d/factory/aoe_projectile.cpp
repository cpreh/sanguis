#include "aoe_projectile.hpp"
#include "../rocket.hpp"
#include "../grenade.hpp"
#include "../../exception.hpp"
#include <fcppt/text.hpp>

sanguis::draw::entity_auto_ptr
sanguis::draw::factory::aoe_projectile(
	environment const &env,
	entity_id const id,
	aoe_projectile_type::type const ptype,
	funit const aoe)
{
	switch(ptype) {
	case aoe_projectile_type::rocket:
		return entity_auto_ptr(
			new rocket(
				env,
				id,
				FCPPT_TEXT("rocket"),
				aoe
			)
		);
	case aoe_projectile_type::grenade:
		return entity_auto_ptr(
			new grenade(
				env,
				id,
				FCPPT_TEXT("grenade"),
				aoe
			)
		);
	default:
		throw exception(
			FCPPT_TEXT("draw::factory::aoe_projectile: missing loading code!")
		);
	}
}
