#ifndef SANGUIS_CLIENT_CONTROL_INPUT_TRANSLATOR_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_INPUT_TRANSLATOR_HPP_INCLUDED

#include <sanguis/client/control/input_translator_fwd.hpp>
#include <sanguis/client/control/actions/binary_type_fwd.hpp>
#include <sanguis/client/control/actions/callback.hpp>
#include <sanguis/client/control/actions/nullary_type_fwd.hpp>
#include <sge/input/event_base_fwd.hpp>
#include <sge/input/cursor/event/button_fwd.hpp>
#include <sge/input/cursor/event/move_fwd.hpp>
#include <sge/input/focus/event/key_fwd.hpp>
#include <fcppt/nonmovable.hpp>

namespace sanguis::client::control
{

class input_translator
{
  FCPPT_NONMOVABLE(input_translator);

public:
  explicit input_translator(sanguis::client::control::actions::callback &&);

  ~input_translator();

  void on_event(sge::input::event_base const &);

private:
  void key_event(sge::input::focus::event::key const &);

  void move_event(sge::input::cursor::event::move const &);

  void button_event(sge::input::cursor::event::button const &);

  void direction_event(sge::input::focus::event::key const &);

  void nullary_event(bool pressed, sanguis::client::control::actions::nullary_type);

  void binary_event(bool pressed, sanguis::client::control::actions::binary_type);

  sanguis::client::control::actions::callback const callback_;
};

}

#endif
