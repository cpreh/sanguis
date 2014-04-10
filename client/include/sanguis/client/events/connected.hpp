#ifndef SANGUIS_CLIENT_EVENTS_CONNECTED_HPP_INCLUDED
#define SANGUIS_CLIENT_EVENTS_CONNECTED_HPP_INCLUDED

#include <sanguis/client/events/connected_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/event.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace events
{

class connected
:
	public boost::statechart::event<
		sanguis::client::events::connected
	>
{
};

}
}
}

#endif
