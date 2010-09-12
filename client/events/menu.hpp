#ifndef SANGUIS_CLIENT_EVENTS_MENU_HPP_INCLUDED
#define SANGUIS_CLIENT_EVENTS_MENU_HPP_INCLUDED

#include "menu_fwd.hpp"
#include <boost/statechart/event.hpp>

namespace sanguis
{
namespace client
{
namespace events
{

class menu
:
	public boost::statechart::event<
		menu
	>
{
};

}
}
}

#endif // SANGUIS_CLIENT_MENU_EVENT_HPP_INCLUDED
