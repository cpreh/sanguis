#ifndef SANGUIS_CLIENT_EVENTS_CONNECTED_HPP_INCLUDED
#define SANGUIS_CLIENT_EVENTS_CONNECTED_HPP_INCLUDED

#include "connected_fwd.hpp"
#include <boost/statechart/event.hpp>

namespace sanguis
{
namespace client
{
namespace events
{

class connected
:
	public boost::statechart::event<
		connected
	>
{
};

}
}
}

#endif
