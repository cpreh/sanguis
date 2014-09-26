#include <sanguis/aoe_projectile_type.hpp>
#include <sanguis/client/draw2d/aoe.hpp>
#include <sanguis/client/draw2d/insert_own_callback.hpp>
#include <sanguis/client/draw2d/entities/aoe_bullet.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/entities/model/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/factory/aoe_projectile.hpp>
#include <sanguis/load/model/aoe_projectile_path.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::client::draw2d::entities::unique_ptr
sanguis::client::draw2d::factory::aoe_projectile(
	sanguis::client::draw2d::entities::model::load_parameters const &_parameters,
	sanguis::client::draw2d::insert_own_callback const &_insert,
	sanguis::aoe_projectile_type const _aoe_projectile_type,
	sanguis::client::draw2d::aoe const _aoe
)
{
	return
		sanguis::client::draw2d::entities::unique_ptr(
			fcppt::make_unique_ptr<
				sanguis::client::draw2d::entities::aoe_bullet
			>(
				_parameters,
				_insert,
				sanguis::load::model::aoe_projectile_path(
					_aoe_projectile_type
				),
				_aoe
			)
		);
}
