#include <sanguis/aoe_projectile_type.hpp>
#include <sanguis/client/draw2d/aoe.hpp>
#include <sanguis/client/draw2d/insert_own_callback.hpp>
#include <sanguis/client/draw2d/factory/aoe_projectile.hpp>
#include <sanguis/client/draw2d/entities/aoe_bullet.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/entities/model/name.hpp>
#include <sanguis/client/draw2d/entities/model/load_parameters_fwd.hpp>
#include <sanguis/load/aoe_projectile_name.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/assert/unreachable.hpp>


sanguis::client::draw2d::entities::unique_ptr
sanguis::client::draw2d::factory::aoe_projectile(
	sanguis::client::draw2d::entities::model::load_parameters const &_parameters,
	sanguis::client::draw2d::insert_own_callback const &_insert,
	sanguis::aoe_projectile_type const _aoe_projectile_type,
	sanguis::client::draw2d::aoe const _aoe
)
{
	switch(
		_aoe_projectile_type
	)
	{
	case sanguis::aoe_projectile_type::rocket:
	case sanguis::aoe_projectile_type::grenade:
		return
			sanguis::client::draw2d::entities::unique_ptr(
				fcppt::make_unique_ptr<
					sanguis::client::draw2d::entities::aoe_bullet
				>(
					_parameters,
					_insert,
					sanguis::client::draw2d::entities::model::name(
						sanguis::load::aoe_projectile_name(
							_aoe_projectile_type
						)
					),
					_aoe
				)
			);
	}

	FCPPT_ASSERT_UNREACHABLE;
}
