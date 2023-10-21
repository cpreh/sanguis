#include <sanguis/aura_type_vector.hpp>
#include <sanguis/buff_type_vector.hpp>
#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/weapon_status.hpp>
#include <sanguis/client/health.hpp>
#include <sanguis/client/health_pair.hpp>
#include <sanguis/client/max_health.hpp>
#include <sanguis/client/optional_health_pair.hpp>
#include <sanguis/client/player_health_callback.hpp>
#include <sanguis/client/draw2d/collide_callback.hpp>
#include <sanguis/client/draw2d/collide_parameters.hpp>
#include <sanguis/client/draw2d/fradius.hpp>
#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/own_player.hpp>
#include <sanguis/client/draw2d/entities/player.hpp>
#include <sanguis/client/draw2d/entities/with_auras_model.hpp>
#include <sanguis/client/draw2d/entities/model/object.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <sanguis/client/load/auras/context_ref.hpp>
#include <sanguis/load/model/radius.hpp>
#include <sanguis/model/cell_size.hpp>
#include <sanguis/model/dim.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/dim/to_unsigned.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::client::draw2d::entities::own_player::own_player(
    sanguis::client::load::auras::context_ref const _auras_load_context,
    sanguis::client::draw2d::entities::load_parameters const &_parameters,
    sanguis::client::draw2d::collide_callback &&_collide,
    sanguis::client::player_health_callback &&_player_health_callback,
    sanguis::optional_primary_weapon_type const _primary_weapon,
    sanguis::weapon_status const _weapon_status,
    sanguis::client::draw2d::speed const &_speed,
    sanguis::client::draw2d::sprite::center const &_center,
    sanguis::client::draw2d::sprite::rotation const _rotation,
    sanguis::aura_type_vector &&_auras,
    sanguis::buff_type_vector &&_buffs,
    sanguis::client::health_pair const _health_pair)
    : sanguis::client::draw2d::entities::player(
          _auras_load_context,
          _parameters,
          _primary_weapon,
          _weapon_status,
          _speed,
          _center,
          _rotation,
          std::move(_auras),
          std::move(_buffs),
          _health_pair),
      collide_(std::move(_collide)),
      player_health_callback_(std::move(_player_health_callback)),
      desired_speed_(fcppt::math::vector::null<sanguis::client::draw2d::speed::value_type>())
{
}

sanguis::client::draw2d::entities::own_player::~own_player() = default;

void sanguis::client::draw2d::entities::own_player::health(sanguis::client::health const _health)
{
  sanguis::client::draw2d::entities::model::object::health(_health);

  this->update_health();
}

void sanguis::client::draw2d::entities::own_player::max_health(
    sanguis::client::max_health const _max_health)
{
  sanguis::client::draw2d::entities::model::object::max_health(_max_health);

  this->update_health();
}

void sanguis::client::draw2d::entities::own_player::speed(
    sanguis::client::draw2d::speed const &_speed)
{
  desired_speed_ = _speed;

  sanguis::client::draw2d::entities::player::speed(_speed);
}

void sanguis::client::draw2d::entities::own_player::update()
{
  fcppt::optional::maybe_void(
      collide_(sanguis::client::draw2d::collide_parameters(
          this->movement_duration(),
          this->float_center(),
          this->speed(),
          sanguis::client::draw2d::fradius(
              sanguis::load::model::radius(
                  sanguis::model::cell_size(
                      fcppt::math::dim::structure_cast<sanguis::model::dim, fcppt::cast::size_fun>(
                          fcppt::math::dim::to_unsigned(this->bounding_dim()))))
                  .get()
                  .value()))),
      [this](sanguis::client::draw2d::speed const &_new_speed)
      { sanguis::client::draw2d::entities::player::speed(_new_speed); });

  sanguis::client::draw2d::entities::player::update();

  sanguis::client::draw2d::entities::player::speed(desired_speed_);
}

void sanguis::client::draw2d::entities::own_player::on_die()
{
  sanguis::client::draw2d::entities::with_auras_model::on_die();

  player_health_callback_(sanguis::client::optional_health_pair());
}

void sanguis::client::draw2d::entities::own_player::update_health()
{
  player_health_callback_(this->health_pair());
}
