#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_PART_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_PART_HPP_INCLUDED

#include <sanguis/diff_clock_cref.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/client/sound_manager_ref.hpp>
#include <sanguis/client/draw2d/entities/model/animation.hpp>
#include <sanguis/client/draw2d/entities/model/desired_orientation.hpp>
#include <sanguis/client/draw2d/entities/model/part_fwd.hpp>
#include <sanguis/client/draw2d/sprite/rotation_fwd.hpp>
#include <sanguis/client/draw2d/sprite/normal/object_fwd.hpp>
#include <sanguis/client/load/animation_type_fwd.hpp>
#include <sanguis/client/load/model/part_cref.hpp>
#include <sge/texture/const_part_ref_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis::client::draw2d::entities::model
{

class part
{
  FCPPT_NONCOPYABLE(part);

public:
  part(
      sanguis::diff_clock_cref,
      sanguis::client::sound_manager_ref,
      sanguis::client::load::model::part_cref,
      sanguis::optional_primary_weapon_type,
      sanguis::client::draw2d::sprite::rotation,
      sanguis::client::load::animation_type);

  part(part &&) noexcept;

  part &operator=(part &&) noexcept;

  ~part();

  void pause(bool);

  void animation(sanguis::client::load::animation_type);

  void weapon(sanguis::optional_primary_weapon_type);

  void update(sanguis::client::draw2d::sprite::normal::object & // NOLINT(google-runtime-references)
  ); // NOLINT(google-runtime-references)

  void orientation(sanguis::client::draw2d::sprite::rotation);

  [[nodiscard]] bool ended() const;

  [[nodiscard]] sge::texture::const_part_ref texture();

private:
  [[nodiscard]] sanguis::client::draw2d::entities::model::animation
      load_animation(sanguis::client::load::animation_type);

  sanguis::diff_clock_cref diff_clock_;

  sanguis::client::sound_manager_ref sound_manager_;

  sanguis::diff_timer rotation_timer_;

  sanguis::client::draw2d::entities::model::desired_orientation desired_orientation_;

  sanguis::client::load::model::part_cref load_part_;

  sanguis::optional_primary_weapon_type weapon_;

  sanguis::client::draw2d::entities::model::animation animation_;
};

}

#endif
