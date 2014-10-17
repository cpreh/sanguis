#include <sanguis/projectile_type.hpp>
#include <sanguis/client/draw2d/entities/bullet.hpp>
#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/factory/projectile.hpp>
#include <sanguis/load/model/projectile_path.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::client::draw2d::entities::unique_ptr
sanguis::client::draw2d::factory::projectile(
	sanguis::client::draw2d::entities::load_parameters const &_parameters,
	sanguis::projectile_type const _projectile_type
)
{
	return
		sanguis::client::draw2d::entities::unique_ptr(
			fcppt::make_unique_ptr<
				sanguis::client::draw2d::entities::bullet
			>(
				_parameters,
				sanguis::load::model::projectile_path(
					_projectile_type
				)
			)
		);
}
