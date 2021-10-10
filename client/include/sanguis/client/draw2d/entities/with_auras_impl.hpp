#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_AURAS_IMPL_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_WITH_AURAS_IMPL_HPP_INCLUDED

#include <sanguis/aura_type.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/duration_second.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/with_auras_decl.hpp>
#include <sanguis/client/draw2d/entities/with_auras_parameters_decl.hpp>
#include <sanguis/client/draw2d/entities/ifaces/with_auras.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <sanguis/client/draw2d/sprite/size_or_texture_size.hpp>
#include <sanguis/client/draw2d/sprite/normal/no_rotation.hpp>
#include <sanguis/client/draw2d/sprite/normal/object.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_decl.hpp>
#include <sanguis/client/draw2d/sprite/normal/white.hpp>
#include <sanguis/client/load/auras/context.hpp>
#include <sge/sprite/intrusive/connection.hpp>
#include <sge/sprite/roles/center.hpp>
#include <sge/sprite/roles/color.hpp>
#include <sge/sprite/roles/connection.hpp>
#include <sge/sprite/roles/rotation.hpp>
#include <sge/sprite/roles/size_or_texture_size.hpp>
#include <sge/sprite/roles/texture0.hpp>
#include <sge/sprite/types/texture_size.hpp>
#include <sge/timer/elapsed_fractional.hpp>
#include <sge/timer/reset_when_expired.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_literal_strong_typedef.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/use.hpp>
#include <fcppt/config/external_begin.hpp>
#include <numbers>
#include <utility>
#include <fcppt/config/external_end.hpp>

template <typename Base>
sanguis::client::draw2d::entities::with_auras<Base>::with_auras(parameters_type const &_parameters)
    : sanguis::client::draw2d::entities::ifaces::with_auras(),
      Base(_parameters.base()),
      aura_load_context_(_parameters.aura_load_context()),
      normal_system_(_parameters.normal_system()),
      rotate_timer_(sanguis::diff_timer::parameters(
          fcppt::make_cref(_parameters.diff_clock()),
          sanguis::duration_second(
              16 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
              ))),
      sprites_()
{
  for (auto const &aura : _parameters.auras())
  {
    this->add_aura(aura);
  }
}

namespace sanguis::client::draw2d::entities
{
template <typename Base>
with_auras<Base>::~with_auras() = default;
}

template <typename Base>
void sanguis::client::draw2d::entities::with_auras<Base>::update()
{
  Base::update();

  for (auto &sprite : sprites_)
  {
    sprite.second.center(this->center().get());

    sprite.second.rotation(
        sge::timer::elapsed_fractional<sanguis::client::draw2d::sprite::rotation::value_type>(
            rotate_timer_) *
        std::numbers::pi_v<sanguis::client::draw2d::sprite::rotation::value_type> *
        fcppt::literal<sanguis::client::draw2d::sprite::rotation::value_type>(2));
  }

  FCPPT_USE(sge::timer::reset_when_expired(fcppt::make_ref(rotate_timer_)));
}

template <typename Base>

void sanguis::client::draw2d::entities::with_auras<Base>::on_die()
{
  Base::on_die();

  sprites_.clear();
}

template <typename Base>
void sanguis::client::draw2d::entities::with_auras<Base>::add_aura(sanguis::aura_type const _aura)
{
  // Multiple inserts are ok
  sprites_.insert(std::make_pair(
      _aura,
      sanguis::client::draw2d::sprite::normal::object(
          sge::sprite::roles::connection{} =
              normal_system_->connection(sanguis::client::draw2d::z_ordering::aura),
          sge::sprite::roles::center{} = this->center().get(),
          sge::sprite::roles::rotation{} =
              sanguis::client::draw2d::sprite::normal::no_rotation().get(),
          sge::sprite::roles::color{} = sanguis::client::draw2d::sprite::normal::white(),
          sge::sprite::roles::texture0{} =
              sanguis::client::draw2d::sprite::normal::object::texture_type{
                  aura_load_context_->texture(_aura)},
          sge::sprite::roles::size_or_texture_size{} =
              sanguis::client::draw2d::sprite::size_or_texture_size{
                  sge::sprite::types::texture_size{}})));
}

#endif
