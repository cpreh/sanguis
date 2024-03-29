#ifndef SANGUIS_SERVER_WEAPONS_EVENTS_RELOAD_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_EVENTS_RELOAD_HPP_INCLUDED

#include <sanguis/server/weapons/events/reload_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/event.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis::server::weapons::events
{

class reload : public boost::statechart::event<sanguis::server::weapons::events::reload>
{
public:
  reload();

  reload(reload &&) noexcept;

  reload(reload const &);

  reload &operator=(reload &&) noexcept;

  reload &operator=(reload const &);

  ~reload() override;
};

}

#endif
