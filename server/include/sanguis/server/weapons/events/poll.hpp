#ifndef SANGUIS_SERVER_WEAPONS_EVENTS_POLL_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_EVENTS_POLL_HPP_INCLUDED

#include <sanguis/server/weapons/events/poll_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/event.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis::server::weapons::events
{

class poll : public boost::statechart::event<sanguis::server::weapons::events::poll>
{
public:
  poll();

  poll(poll &&) noexcept;

  poll(poll const &);

  poll &operator=(poll &&) noexcept;

  poll &operator=(poll const &);

  ~poll() override;
};

}

#endif
