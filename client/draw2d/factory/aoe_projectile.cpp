#include "aoe_projectile.hpp"
#include "../entities/aoe_bullet.hpp"
#include "../../load/aoe_projectile_name.hpp"
#include "../../exception.hpp"
#include <fcppt/text.hpp>

sanguis::client::draw2d::entities::auto_ptr
sanguis::client::draw2d::factory::aoe_projectile(
	model::parameters const &param,
	sprite::particle::system &particle_system,
	insert_callback const &insert,
	aoe_projectile_type::type const ptype,
	funit const aoe
)
{
	switch(ptype)
	{
	case aoe_projectile_type::aoe_projectile:
		break;
	case aoe_projectile_type::rocket:
	case aoe_projectile_type::grenade:
		return entities::auto_ptr(
			new entities::aoe_bullet(
				param,
				particle_system,
				insert,
				load::aoe_projectile_name(
					ptype
				)
				aoe
			)
		);
	}

	throw exception(
		FCPPT_TEXT("draw::factory::aoe_projectile: missing loading code!")
	);
}
