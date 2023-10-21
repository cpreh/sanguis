#include <sanguis/aura_type_vector.hpp>
#include <sanguis/buff_type_vector.hpp>
#include <sanguis/friend_type.hpp>
#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/weapon_status.hpp>
#include <sanguis/client/health_pair.hpp>
#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/z_ordering_vector.hpp>
#include <sanguis/client/draw2d/entities/friend.hpp>
#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/order_function_from_vector.hpp>
#include <sanguis/client/draw2d/entities/sentry.hpp>
#include <sanguis/client/draw2d/entities/model/object.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/draw2d/sprite/index.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <sanguis/client/load/auras/context_ref.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)

// NOLINTNEXTLINE(fuchsia-statically-constructed-objects,cert-err58-cpp)
sanguis::client::draw2d::sprite::index const top{1U};

FCPPT_PP_POP_WARNING

}

sanguis::client::draw2d::entities::sentry::sentry(
    sanguis::client::draw2d::entities::load_parameters const &_load_parameters,
    sanguis::client::load::auras::context_ref const _aura_resources,
    sanguis::optional_primary_weapon_type const _primary_weapon,
    sanguis::weapon_status const _weapon_status,
    sanguis::client::draw2d::speed const &_speed,
    sanguis::client::draw2d::sprite::center const &_center,
    sanguis::client::draw2d::sprite::rotation const _rotation,
    sanguis::aura_type_vector &&_auras,
    sanguis::buff_type_vector &&_buffs,
    sanguis::client::health_pair const _health_pair)
    : sanguis::client::draw2d::entities::friend_(
          _load_parameters,
          _aura_resources,
          sanguis::friend_type::sentry,
          _primary_weapon,
          _weapon_status,
          _speed,
          _center,
          _rotation,
          std::move(_auras),
          std::move(_buffs),
          sanguis::client::draw2d::entities::order_function_from_vector(
              sanguis::client::draw2d::z_ordering_vector{
                  sanguis::client::draw2d::z_ordering::player_lower,
                  sanguis::client::draw2d::z_ordering::player_upper}),
          _health_pair)
{
}

sanguis::client::draw2d::entities::sentry::~sentry() = default;

void sanguis::client::draw2d::entities::sentry::orientation(
    sanguis::client::draw2d::sprite::rotation const _rotation)
{
  sanguis::client::draw2d::entities::model::object::orientation(_rotation, top);
}
