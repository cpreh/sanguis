#include <sanguis/aoe_projectile_type.hpp>
#include <sanguis/client/draw2d/aoe.hpp>
#include <sanguis/client/draw2d/insert_own_callback.hpp>
#include <sanguis/client/draw2d/factory/aoe_projectile.hpp>
#include <sanguis/client/draw2d/entities/aoe_bullet.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/entities/model/parameters_fwd.hpp>
#include <sanguis/load/aoe_projectile_name.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/assert/unreachable.hpp>


sanguis::client::draw2d::entities::unique_ptr
sanguis::client::draw2d::factory::aoe_projectile(
	sanguis::client::draw2d::entities::model::parameters const &_param,
	sanguis::client::draw2d::insert_own_callback const &_insert,
	sanguis::aoe_projectile_type::type const _ptype,
	sanguis::client::draw2d::aoe const _aoe
)
{
	switch(
		_ptype
	)
	{
	case sanguis::aoe_projectile_type::aoe_damage:
	case sanguis::aoe_projectile_type::size:
		break;
	case sanguis::aoe_projectile_type::rocket:
	case sanguis::aoe_projectile_type::grenade:
		return
			sanguis::client::draw2d::entities::unique_ptr(
				fcppt::make_unique_ptr<
					sanguis::client::draw2d::entities::aoe_bullet
				>(
					fcppt::cref(
						_param
					),
					_insert,
					sanguis::load::aoe_projectile_name(
						_ptype
					),
					_aoe
				)
			);
	}

	FCPPT_ASSERT_UNREACHABLE;
}
