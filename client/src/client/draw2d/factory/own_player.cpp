#include <sanguis/aura_type_vector.hpp>
#include <sanguis/buff_type_vector.hpp>
#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/weapon_status.hpp>
#include <sanguis/client/health_pair.hpp>
#include <sanguis/client/player_health_callback.hpp>
#include <sanguis/client/draw2d/collide_callback.hpp>
#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/client/draw2d/entities/base.hpp>
#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/own_player.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/factory/own_player.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <sanguis/client/load/auras/context_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::client::draw2d::entities::unique_ptr sanguis::client::draw2d::factory::own_player(
    sanguis::client::load::auras::context_ref const _auras_load_context,
    sanguis::client::draw2d::entities::load_parameters const &_parameters,
    sanguis::client::draw2d::collide_callback &&_collide_callback,
    sanguis::client::player_health_callback &&_player_health_callback,
    sanguis::optional_primary_weapon_type const _primary_weapon_type,
    sanguis::weapon_status const _weapon_status,
    sanguis::client::draw2d::speed const &_speed,
    sanguis::client::draw2d::sprite::center const &_center,
    sanguis::client::draw2d::sprite::rotation const _rotation,
    sanguis::aura_type_vector &&_auras,
    sanguis::buff_type_vector &&_buffs,
    sanguis::client::health_pair const _health_pair)
{
  return fcppt::unique_ptr_to_base<sanguis::client::draw2d::entities::base>(
      fcppt::make_unique_ptr<sanguis::client::draw2d::entities::own_player>(
          _auras_load_context,
          _parameters,
          std::move(_collide_callback),
          std::move(_player_health_callback),
          _primary_weapon_type,
          _weapon_status,
          _speed,
          _center,
          _rotation,
          std::move(_auras),
          std::move(_buffs),
          _health_pair));
}
