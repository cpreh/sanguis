#ifndef SANGUIS_CLIENT_MENU_EVENT_HPP_INCLUDED
#define SANGUIS_CLIENT_MENU_EVENT_HPP_INCLUDED

#include <boost/statechart/event.hpp>

namespace sanguis
{
namespace client
{
class menu_event : public boost::statechart::event<menu_event> 
{
};
}
}

#endif // SANGUIS_CLIENT_MENU_EVENT_HPP_INCLUDED
