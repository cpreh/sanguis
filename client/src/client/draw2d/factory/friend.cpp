#include <sanguis/aura_type_vector.hpp>
#include <sanguis/buff_type_vector.hpp>
#include <sanguis/friend_type.hpp>
#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/weapon_status.hpp>
#include <sanguis/client/health_pair.hpp>
#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/base.hpp>
#include <sanguis/client/draw2d/entities/constant_order.hpp>
#include <sanguis/client/draw2d/entities/friend.hpp>
#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/sentry.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/factory/friend.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <sanguis/client/load/auras/context_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::client::draw2d::entities::unique_ptr sanguis::client::draw2d::factory::friend_(
    sanguis::client::draw2d::entities::load_parameters const &_parameters,
    sanguis::client::load::auras::context_ref const _aura_load_context,
    sanguis::friend_type const _friend_type,
    sanguis::optional_primary_weapon_type const _primary_weapon_type,
    sanguis::weapon_status const _weapon_status,
    sanguis::client::draw2d::speed const &_speed,
    sanguis::client::draw2d::sprite::center const &_center,
    sanguis::client::draw2d::sprite::rotation const _rotation,
    sanguis::aura_type_vector &&_auras,
    sanguis::buff_type_vector &&_buffs,
    sanguis::client::health_pair const _health_pair)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_friend_type)
  {
  case sanguis::friend_type::spider:
    return fcppt::unique_ptr_to_base<sanguis::client::draw2d::entities::base>(
        fcppt::make_unique_ptr<sanguis::client::draw2d::entities::friend_>(
            _parameters,
            _aura_load_context,
            _friend_type,
            _primary_weapon_type,
            _weapon_status,
            _speed,
            _center,
            _rotation,
            std::move(_auras),
            std::move(_buffs),
            sanguis::client::draw2d::entities::constant_order(
                sanguis::client::draw2d::z_ordering::model_generic),
            _health_pair));
  case sanguis::friend_type::sentry:
    return fcppt::unique_ptr_to_base<sanguis::client::draw2d::entities::base>(
        fcppt::make_unique_ptr<sanguis::client::draw2d::entities::sentry>(
            _parameters,
            _aura_load_context,
            _primary_weapon_type,
            _weapon_status,
            _speed,
            _center,
            _rotation,
            std::move(_auras),
            std::move(_buffs),
            _health_pair));
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_friend_type);
}
