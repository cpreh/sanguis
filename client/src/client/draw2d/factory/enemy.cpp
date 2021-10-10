#include <sanguis/aura_type_vector.hpp>
#include <sanguis/buff_type_vector.hpp>
#include <sanguis/enemy_kind.hpp>
#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/weapon_status.hpp>
#include <sanguis/client/health_pair.hpp>
#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/client/draw2d/entities/base.hpp>
#include <sanguis/client/draw2d/entities/enemy.hpp>
#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/name_fwd.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/factory/enemy.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <sanguis/client/load/auras/context_ref.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::client::draw2d::entities::unique_ptr sanguis::client::draw2d::factory::enemy(
    sanguis::client::draw2d::entities::load_parameters const &_parameters,
    sanguis::client::load::auras::context_ref const _aura_resources,
    sanguis::creator::enemy_type const _enemy_type,
    sanguis::enemy_kind const _enemy_kind,
    sanguis::optional_primary_weapon_type const _primary_weapon_type,
    sanguis::weapon_status const _weapon_status,
    sanguis::client::draw2d::speed const &_speed,
    sanguis::client::draw2d::sprite::center const &_center,
    sanguis::client::draw2d::sprite::rotation const _rotation,
    sanguis::aura_type_vector &&_auras,
    sanguis::buff_type_vector &&_buffs,
    sanguis::client::draw2d::entities::name const &_name,
    sanguis::client::health_pair const _health_pair)
{
  return fcppt::unique_ptr_to_base<sanguis::client::draw2d::entities::base>(
      fcppt::make_unique_ptr<sanguis::client::draw2d::entities::enemy>(
          _parameters,
          _aura_resources,
          _enemy_type,
          _enemy_kind,
          _primary_weapon_type,
          _weapon_status,
          _speed,
          _center,
          _rotation,
          std::move(_auras),
          std::move(_buffs),
          _name,
          _health_pair));
}
