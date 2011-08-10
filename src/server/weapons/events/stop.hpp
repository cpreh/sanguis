#ifndef SANGUIS_SERVER_WEAPONS_EVENTS_STOP_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_EVENTS_STOP_HPP_INCLUDED

#include "stop_fwd.hpp"
#include <boost/statechart/event.hpp>

namespace sanguis
{
namespace server
{
namespace weapons
{
namespace events
{

class stop
:
	public boost::statechart::event<
		stop
	>
{};

}
}
}
}

#endif
