#include <sanguis/projectile_type.hpp>
#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/client/draw2d/entities/base.hpp>
#include <sanguis/client/draw2d/entities/bullet.hpp>
#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/factory/projectile.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <sanguis/load/model/projectile_path.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>

sanguis::client::draw2d::entities::unique_ptr sanguis::client::draw2d::factory::projectile(
    sanguis::client::draw2d::entities::load_parameters const &_parameters,
    sanguis::projectile_type const _projectile_type,
    sanguis::client::draw2d::speed const &_speed,
    sanguis::client::draw2d::sprite::center const &_center,
    sanguis::client::draw2d::sprite::rotation const _rotation)
{
  return fcppt::unique_ptr_to_base<sanguis::client::draw2d::entities::base>(
      fcppt::make_unique_ptr<sanguis::client::draw2d::entities::bullet>(
          _parameters,
          _speed,
          _center,
          _rotation,
          sanguis::load::model::projectile_path(_projectile_type)));
}
