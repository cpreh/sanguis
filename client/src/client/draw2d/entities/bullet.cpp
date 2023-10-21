#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/weapon_status.hpp>
#include <sanguis/client/optional_health_pair.hpp>
#include <sanguis/client/draw2d/center.hpp>
#include <sanguis/client/draw2d/funit.hpp>
#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/client/draw2d/vector2.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/z_ordering_vector.hpp>
#include <sanguis/client/draw2d/entities/bullet.hpp>
#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/order_function_from_vector.hpp>
#include <sanguis/client/draw2d/entities/model/decay_option.hpp>
#include <sanguis/client/draw2d/entities/model/object.hpp>
#include <sanguis/client/draw2d/entities/model/parameters.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/draw2d/sprite/index.hpp>
#include <sanguis/client/draw2d/sprite/point.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <sanguis/client/draw2d/sprite/unit.hpp>
#include <sanguis/client/draw2d/sprite/normal/object.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/client/draw2d/sprite/normal/white.hpp>
#include <sanguis/load/model/path_fwd.hpp>
#include <fcppt/const.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/cast/float_to_int.hpp>
#include <fcppt/cast/float_to_int_fun.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/cast/int_to_float_fun.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/length.hpp>
#include <fcppt/math/vector/normalize.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)

// NOLINTNEXTLINE(fuchsia-statically-constructed-objects,cert-err58-cpp)
sanguis::client::draw2d::sprite::index const tail{1U};

FCPPT_PP_POP_WARNING

}

sanguis::client::draw2d::entities::bullet::bullet(
    sanguis::client::draw2d::entities::load_parameters const &_parameters,
    sanguis::client::draw2d::speed const &_speed,
    sanguis::client::draw2d::sprite::center const &_center,
    sanguis::client::draw2d::sprite::rotation const _rotation,
    sanguis::load::model::path &&_path)
    : sanguis::client::draw2d::entities::model::object(
          sanguis::client::draw2d::entities::model::parameters(
              _parameters,
              std::move(_path),
              sanguis::client::draw2d::entities::order_function_from_vector(
                  sanguis::client::draw2d::z_ordering_vector{
                      sanguis::client::draw2d::z_ordering::bullet,
                      sanguis::client::draw2d::z_ordering::bullet_tail}),
              sanguis::client::optional_health_pair(),
              sanguis::client::draw2d::entities::model::decay_option::immediate,
              sanguis::optional_primary_weapon_type(),
              sanguis::weapon_status::nothing,
              _speed,
              _center,
              _rotation,
              sanguis::client::draw2d::sprite::normal::white())),
      origin_(_center)
{
  this->at(tail).w(fcppt::literal<sanguis::client::draw2d::sprite::unit>(3));
}

sanguis::client::draw2d::entities::bullet::~bullet() = default;

void sanguis::client::draw2d::entities::bullet::update()
{
  sanguis::client::draw2d::entities::model::object::update();

  sanguis::client::draw2d::funit const max_tail_length(
      fcppt::literal<sanguis::client::draw2d::funit>(
          240 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
          ));

  sanguis::client::draw2d::funit const tail_length(std::min(
      fcppt::math::vector::length<sanguis::client::draw2d::funit>((origin_ - this->center()).get()),
      max_tail_length));

  sanguis::client::draw2d::center const cur_center(
      fcppt::math::vector::structure_cast<
          sanguis::client::draw2d::center::value_type,
          fcppt::cast::int_to_float_fun>(this->center().get()));

  sanguis::client::draw2d::center const new_center(fcppt::optional::maybe(
      fcppt::math::vector::normalize(this->speed().get()),
      fcppt::const_(cur_center),
      [this, tail_length, cur_center](sanguis::client::draw2d::vector2 const &_normal)
      {
        return sanguis::client::draw2d::center(
            cur_center.get() -
            _normal *
                fcppt::literal<sanguis::client::draw2d::funit>(
                    0.5 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                    ) *
                fcppt::math::vector::length(sanguis::client::draw2d::vector2(
                    tail_length,
                    fcppt::cast::int_to_float<sanguis::client::draw2d::funit>(
                        this->at(tail).size().h()))));
      }));

  this->at(tail).center(fcppt::math::vector::structure_cast<
                        sanguis::client::draw2d::sprite::point,
                        fcppt::cast::float_to_int_fun>(new_center.get()));

  this->at(tail).w(fcppt::cast::float_to_int<sanguis::client::draw2d::sprite::unit>(tail_length));
}
