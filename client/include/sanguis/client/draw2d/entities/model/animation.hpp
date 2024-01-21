#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_ANIMATION_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_ANIMATION_HPP_INCLUDED

#include <sanguis/client/draw2d/entities/model/animation_fwd.hpp> // IWYU pragma: keep
#include <sanguis/client/draw2d/entities/model/optional_sound.hpp>
#include <sanguis/client/draw2d/sprite/animation/texture.hpp>
#include <sanguis/client/load/animation_type.hpp>
#include <sge/texture/const_part_ref_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis::client::draw2d::entities::model
{

class animation
{
  FCPPT_NONCOPYABLE(animation);

public:
  animation(
      sanguis::client::draw2d::sprite::animation::texture &&,
      sanguis::client::load::animation_type,
      sanguis::client::draw2d::entities::model::optional_sound &&);

  animation(animation &&) noexcept;

  animation &operator=(animation &&) noexcept;

  ~animation();

  [[nodiscard]] sanguis::client::load::animation_type animation_type() const;

  [[nodiscard]] sge::texture::const_part_ref current_texture();

  [[nodiscard]] sanguis::client::draw2d::entities::model::optional_sound const &sound() const;

  [[nodiscard]] bool ended() const;

private:
  sanguis::client::draw2d::sprite::animation::texture texture_animation_;

  sanguis::client::load::animation_type animation_type_;

  sanguis::client::draw2d::entities::model::optional_sound sound_;
};

}

#endif
