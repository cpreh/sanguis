#include <sanguis/aoe_projectile_type.hpp>
#include <sanguis/client/draw2d/aoe.hpp>
#include <sanguis/client/draw2d/insert_own_callback.hpp>
#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/client/draw2d/entities/aoe_bullet.hpp>
#include <sanguis/client/draw2d/entities/base.hpp>
#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/factory/aoe_projectile.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <sanguis/load/model/aoe_projectile_path.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::client::draw2d::entities::unique_ptr sanguis::client::draw2d::factory::aoe_projectile(
    sanguis::client::draw2d::entities::load_parameters const &_parameters,
    sanguis::client::draw2d::insert_own_callback &&_insert,
    sanguis::aoe_projectile_type const _aoe_projectile_type,
    sanguis::client::draw2d::speed const &_speed,
    sanguis::client::draw2d::sprite::center const &_center,
    sanguis::client::draw2d::sprite::rotation const _rotation,
    sanguis::client::draw2d::aoe const _aoe)
{
  return fcppt::unique_ptr_to_base<sanguis::client::draw2d::entities::base>(
      fcppt::make_unique_ptr<sanguis::client::draw2d::entities::aoe_bullet>(
          _parameters,
          std::move(_insert),
          sanguis::load::model::aoe_projectile_path(_aoe_projectile_type),
          _speed,
          _center,
          _rotation,
          _aoe));
}
