#ifndef SANGUIS_SERVER_WEAPONS_EVENTS_RESET_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_EVENTS_RESET_HPP_INCLUDED

#include "reset_fwd.hpp"
#include <boost/statechart/event.hpp>

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
