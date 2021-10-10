#ifndef SANGUIS_MODEL_ANIMATION_HPP_INCLUDED
#define SANGUIS_MODEL_ANIMATION_HPP_INCLUDED

#include <sanguis/model/animation_fwd.hpp>
#include <sanguis/model/animation_range.hpp>
#include <sanguis/model/optional_animation_delay.hpp>
#include <sanguis/model/optional_animation_sound.hpp>
#include <sanguis/model/optional_image_name.hpp>
#include <sanguis/model/symbol.hpp>

namespace sanguis::model
{

class animation
{
public:
  SANGUIS_MODEL_SYMBOL
  animation(
      sanguis::model::animation_range,
      sanguis::model::optional_animation_delay,
      sanguis::model::optional_animation_sound &&,
      sanguis::model::optional_image_name &&);

  SANGUIS_MODEL_SYMBOL
  animation(animation const &);

  SANGUIS_MODEL_SYMBOL
  animation(animation &&) noexcept;

  SANGUIS_MODEL_SYMBOL
  animation &operator=(animation const &);

  SANGUIS_MODEL_SYMBOL
  animation &operator=(animation &&) noexcept;

  SANGUIS_MODEL_SYMBOL
  ~animation();

  [[nodiscard]] SANGUIS_MODEL_SYMBOL sanguis::model::animation_range animation_range() const;

  [[nodiscard]] SANGUIS_MODEL_SYMBOL sanguis::model::optional_animation_delay
  animation_delay() const;

  SANGUIS_MODEL_SYMBOL
  void animation_delay(sanguis::model::optional_animation_delay);

  [[nodiscard]] SANGUIS_MODEL_SYMBOL sanguis::model::optional_animation_sound
  animation_sound() const;

  SANGUIS_MODEL_SYMBOL
  void animation_sound(sanguis::model::optional_animation_sound const &);

  [[nodiscard]] SANGUIS_MODEL_SYMBOL sanguis::model::optional_image_name const &image_name() const;

private:
  sanguis::model::animation_range animation_range_;

  sanguis::model::optional_animation_delay animation_delay_;

  sanguis::model::optional_animation_sound animation_sound_;

  sanguis::model::optional_image_name image_name_;
};

}

#endif
