#ifndef SANGUIS_SERVER_WEAPONS_EVENTS_STOP_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_EVENTS_STOP_HPP_INCLUDED

#include <sanguis/server/weapons/events/stop_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/event.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis::server::weapons::events
{

class stop : public boost::statechart::event<sanguis::server::weapons::events::stop>
{
public:
  stop();

  stop(stop &&) noexcept;

  stop(stop const &);

  stop &operator=(stop &&) noexcept;

  stop &operator=(stop const &);

  ~stop() override;
};

}

#endif
