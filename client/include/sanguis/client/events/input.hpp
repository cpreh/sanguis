#ifndef SANGUIS_CLIENT_EVENTS_INPUT_HPP_INCLUDED
#define SANGUIS_CLIENT_EVENTS_INPUT_HPP_INCLUDED

#include <sanguis/client/events/input_fwd.hpp>
#include <sge/input/event_base_fwd.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/event.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis::client::events
{

class input : public boost::statechart::event<sanguis::client::events::input>
{
public:
  using event_base_cref = fcppt::reference<sge::input::event_base const>;

  explicit input(event_base_cref);

  input(input &&) noexcept;

  input(input const &);

  input &operator=(input &&) noexcept;

  input &operator=(input const &);

  ~input() override;

  sge::input::event_base const &get() const;

private:
  event_base_cref event_;
};

}

#endif
