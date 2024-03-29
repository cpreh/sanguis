#include <sanguis/aura_type_vector.hpp>
#include <sanguis/buff_type_vector.hpp>
#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/weapon_status.hpp>
#include <sanguis/client/health_pair.hpp>
#include <sanguis/client/optional_health_pair.hpp>
#include <sanguis/client/draw2d/dim2.hpp>
#include <sanguis/client/draw2d/funit.hpp>
#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/client/draw2d/vector2.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/z_ordering_vector.hpp>
#include <sanguis/client/draw2d/entities/load_parameters.hpp>
#include <sanguis/client/draw2d/entities/order_function_from_vector.hpp>
#include <sanguis/client/draw2d/entities/player.hpp>
#include <sanguis/client/draw2d/entities/with_auras_model_parameters.hpp>
#include <sanguis/client/draw2d/entities/with_buffs_auras_model.hpp>
#include <sanguis/client/draw2d/entities/with_buffs_auras_model_parameters.hpp>
#include <sanguis/client/draw2d/entities/model/decay_option.hpp>
#include <sanguis/client/draw2d/entities/model/object.hpp>
#include <sanguis/client/draw2d/entities/model/parameters.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/draw2d/sprite/dim.hpp>
#include <sanguis/client/draw2d/sprite/index.hpp>
#include <sanguis/client/draw2d/sprite/point.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <sanguis/client/draw2d/sprite/unit.hpp>
#include <sanguis/client/draw2d/sprite/normal/object.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/client/draw2d/sprite/normal/white.hpp>
#include <sanguis/client/load/auras/context_ref.hpp>
#include <sanguis/load/model/player_path.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/cast/float_to_int_fun.hpp>
#include <fcppt/cast/int_to_float_fun.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/dim/to_vector.hpp>
#include <fcppt/math/vector/atan2.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/math/vector/point_rotate.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/optional/maybe_void.hpp>
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
FCPPT_PP_DISABLE_CLANG_WARNING(-Wexit-time-destructors)

// NOLINTNEXTLINE(fuchsia-statically-constructed-objects,cert-err58-cpp)
sanguis::client::draw2d::sprite::point const player_body_center(
    24, // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
    48 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
);

// NOLINTNEXTLINE(fuchsia-statically-constructed-objects,cert-err58-cpp)
sanguis::client::draw2d::sprite::index const top(1U);

// NOLINTNEXTLINE(fuchsia-statically-constructed-objects,cert-err58-cpp)
sanguis::client::draw2d::sprite::index const bottom(0U);

FCPPT_PP_POP_WARNING

}

sanguis::client::draw2d::entities::player::player(
    sanguis::client::load::auras::context_ref const _auras_load_context,
    sanguis::client::draw2d::entities::load_parameters const &_load_parameters,
    sanguis::optional_primary_weapon_type const _primary_weapon,
    sanguis::weapon_status const _weapon_status,
    sanguis::client::draw2d::speed const &_speed,
    sanguis::client::draw2d::sprite::center const &_center,
    sanguis::client::draw2d::sprite::rotation const _rotation,
    sanguis::aura_type_vector &&_auras,
    sanguis::buff_type_vector &&_buffs,
    sanguis::client::health_pair const _health_pair)
    : sanguis::client::draw2d::entities::with_buffs_auras_model(
          sanguis::client::draw2d::entities::with_buffs_auras_model_parameters(
              fcppt::make_cref(_load_parameters.diff_clock()),
              fcppt::make_ref(_load_parameters.normal_system()),
              fcppt::make_cref(_load_parameters.collection()),
              std::move(_buffs),
              sanguis::client::draw2d::entities::with_auras_model_parameters(
                  fcppt::make_cref(_load_parameters.diff_clock()),
                  _auras_load_context,
                  fcppt::make_ref(_load_parameters.normal_system()),
                  std::move(_auras),
                  sanguis::client::draw2d::entities::model::parameters(
                      _load_parameters,
                      sanguis::load::model::player_path(),
                      sanguis::client::draw2d::entities::order_function_from_vector(
                          sanguis::client::draw2d::z_ordering_vector{
                              sanguis::client::draw2d::z_ordering::player_lower,
                              sanguis::client::draw2d::z_ordering::player_upper}),
                      sanguis::client::optional_health_pair(_health_pair),
                      sanguis::client::draw2d::entities::model::decay_option::delayed,
                      _primary_weapon,
                      _weapon_status,
                      _speed,
                      _center,
                      _rotation,
                      sanguis::client::draw2d::sprite::normal::white()))))
{
}

sanguis::client::draw2d::entities::player::~player() = default;

void sanguis::client::draw2d::entities::player::speed(sanguis::client::draw2d::speed const &_speed)
{
  sanguis::client::draw2d::entities::model::object::speed(_speed);

  fcppt::optional::maybe_void(
      fcppt::math::vector::atan2(_speed.get()),
      [this](sanguis::client::draw2d::funit const _rotation)
      {
        sanguis::client::draw2d::entities::model::object::orientation(
            sanguis::client::draw2d::sprite::rotation{_rotation}, bottom);
      });
}

void sanguis::client::draw2d::entities::player::orientation(
    sanguis::client::draw2d::sprite::rotation const _orientation)
{
  sanguis::client::draw2d::entities::model::object::orientation(_orientation, top);
}

void sanguis::client::draw2d::entities::player::update()
{
  sanguis::client::draw2d::entities::with_buffs_auras_model::update();

  auto const body_center(fcppt::math::vector::structure_cast<
                         sanguis::client::draw2d::vector2,
                         fcppt::cast::int_to_float_fun>(player_body_center));

  sanguis::client::draw2d::sprite::rotation const sprite_rotation(this->at(top).rotation());

  sanguis::client::draw2d::vector2 const new_rotation(fcppt::math::vector::point_rotate(
      body_center,
      fcppt::math::dim::to_vector(
          fcppt::math::dim::
              structure_cast<sanguis::client::draw2d::dim2, fcppt::cast::int_to_float_fun>(
                  (this->at(top).size() / fcppt::literal<sanguis::client::draw2d::sprite::unit>(2))
                      .get_unsafe())),
      sprite_rotation.get()));

  this->at(top).center(
      this->at(top).center() -
      fcppt::math::vector::
          structure_cast<sanguis::client::draw2d::sprite::point, fcppt::cast::float_to_int_fun>(
              new_rotation) +
      (this->bounding_dim() / fcppt::literal<sanguis::client::draw2d::sprite::unit>(2))
          .get_unsafe());
}

sanguis::client::draw2d::sprite::dim sanguis::client::draw2d::entities::player::bounding_dim() const
{
  return this->at(top).size();
}
