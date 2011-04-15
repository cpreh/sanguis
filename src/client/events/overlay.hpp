#ifndef SANGUIS_CLIENT_EVENTS_OVERLAY_HPP_INCLUDED
#define SANGUIS_CLIENT_EVENTS_OVERLAY_HPP_INCLUDED

#include "overlay_fwd.hpp"
#include <boost/statechart/event.hpp>

namespace sanguis
{
namespace client
{
namespace events
{

class overlay
:
	public boost::statechart::event<
		overlay
	>
{
};

}
}
}

#endif
