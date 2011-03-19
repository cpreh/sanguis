#include "aoe_projectile.hpp"
#include "../entities/aoe_bullet.hpp"
#include "../../../load/aoe_projectile_name.hpp"
#include "../../../exception.hpp"
#include <fcppt/text.hpp>

sanguis::client::draw2d::entities::auto_ptr
sanguis::client::draw2d::factory::aoe_projectile(
	entities::model::parameters const &_param,
	sprite::particle::system &_particle_system,
	insert_callback const &_insert,
	aoe_projectile_type::type const _ptype,
	funit const _aoe
)
{
	switch(
		_ptype
	)
	{
	case aoe_projectile_type::aoe_damage:
	case aoe_projectile_type::size:
		break;
	case aoe_projectile_type::rocket:
	case aoe_projectile_type::grenade:
		return
			entities::auto_ptr(
				new entities::aoe_bullet(
					_param,
					_particle_system,
					_insert,
					load::aoe_projectile_name(
						_ptype
					),
					_aoe
				)
			);
	}

	throw sanguis::exception(
		FCPPT_TEXT("draw::factory::aoe_projectile: missing loading code!")
	);
}
