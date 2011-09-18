#ifndef SANGUIS_SERVER_WEAPONS_EVENTS_RESET_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_EVENTS_RESET_HPP_INCLUDED

#include <sanguis/server/weapons/events/reset_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/event.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace server
{
namespace weapons
{
namespace events
{

class reset
:
	public boost::statechart::event<
		reset
	>
{};

}
}
}
}

#endif
