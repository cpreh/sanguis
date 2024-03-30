#include <sanguis/client/sound_manager.hpp>
#include <sanguis/client/draw2d/entities/model/make_sound.hpp>
#include <sanguis/client/draw2d/entities/model/optional_sound.hpp>
#include <sanguis/client/draw2d/sprite/animation/loop_method.hpp>
#include <sge/audio/buffer.hpp> // NOLINT(misc-include-cleaner)
#include <sge/audio/buffer_ref.hpp>
#include <sge/audio/sound/base.hpp> // NOLINT(misc-include-cleaner)
#include <sge/audio/sound/base_unique_ptr.hpp>
#include <sge/audio/sound/nonpositional_parameters.hpp>
#include <sge/audio/sound/repeat.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::client::draw2d::entities::model::optional_sound
sanguis::client::draw2d::entities::model::make_sound(
    sge::audio::buffer_ref const _buffer,
    sanguis::client::sound_manager &_sound_manager,
    sanguis::client::draw2d::sprite::animation::loop_method const _loop_method)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_loop_method)
  {
  case sanguis::client::draw2d::sprite::animation::loop_method::stop_at_end:
    _sound_manager.add(
        _buffer->create_nonpositional(sge::audio::sound::nonpositional_parameters()));

    return sanguis::client::draw2d::entities::model::optional_sound();
  case sanguis::client::draw2d::sprite::animation::loop_method::repeat:
  {
    sge::audio::sound::base_unique_ptr new_sound(
        _buffer->create_nonpositional(sge::audio::sound::nonpositional_parameters()));

    new_sound->play(sge::audio::sound::repeat::loop);

    return sanguis::client::draw2d::entities::model::optional_sound{std::move(new_sound)};
  }
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_loop_method);
}
