#ifndef SANGUIS_CLIENT_STATES_UNPAUSED_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_UNPAUSED_HPP_INCLUDED

#include "running.hpp"
#include "../message_event.hpp"
#include "../../tick_event.hpp"
#include <boost/statechart/state.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/result.hpp>
#include <boost/mpl/list.hpp>

namespace sanguis
{
namespace client
{
namespace states
{
class unpaused
	: public boost::statechart::state<unpaused,running>
{
public:
	typedef boost::mpl::list<
		boost::statechart::custom_reaction<tick_event>,
		boost::statechart::custom_reaction<message_event>
	> reactions;

	unpaused(my_context);
	boost::statechart::result react(tick_event const &);
	boost::statechart::result react(message_event const &);
	
	boost::statechart::result operator()(messages::pause const &);
private:
	boost::statechart::result handle_default_msg(messages::base const &);
};
}
}
}

#endif
