#include <sanguis/client/draw2d/factory/aoe_projectile.hpp>
#include <sanguis/client/draw2d/entities/aoe_bullet.hpp>
#include <sanguis/load/aoe_projectile_name.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>

sanguis::client::draw2d::entities::unique_ptr
sanguis::client::draw2d::factory::aoe_projectile(
	entities::model::parameters const &_param,
	sprite::particle::system &_particle_system,
	draw2d::insert_own_callback const &_insert,
	aoe_projectile_type::type const _ptype,
	draw2d::aoe const _aoe
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
			entities::unique_ptr(
				fcppt::make_unique_ptr<
					entities::aoe_bullet
				>(
					fcppt::cref(
						_param
					),
					fcppt::ref(
						_particle_system
					),
					_insert,
					load::aoe_projectile_name(
						_ptype
					),
					_aoe
				)
			);
	}

	FCPPT_ASSERT_UNREACHABLE
}
