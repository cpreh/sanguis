#ifndef SANGUIS_CLIENT_EVENTS_RENDER_HPP_INCLUDED
#define SANGUIS_CLIENT_EVENTS_RENDER_HPP_INCLUDED

#include "render_fwd.hpp"
#include <boost/statechart/event.hpp>

namespace sanguis
{
namespace client
{
namespace events
{

class render
:
	public boost::statechart::event<
		render
	>
{
};

}
}
}

#endif
