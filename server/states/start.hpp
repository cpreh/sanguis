#ifndef SANGUIS_SERVER_STATES_START_HPP_INCLUDED
#define SANGUIS_SERVER_STATES_START_HPP_INCLUDED

#include "../machine.hpp"
#include "../message_event.hpp"
#include "../../tick_event.hpp"
#include <sge/log/fwd.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/result.hpp>
#include <boost/mpl/list.hpp>

namespace sanguis
{
namespace server
{
namespace states
{

struct start
	: public boost::statechart::simple_state<start,machine>
{
	typedef boost::mpl::list<
		boost::statechart::custom_reaction<tick_event>,
		boost::statechart::custom_reaction<message_event> 
		> reactions;

	start();
	boost::statechart::result react(tick_event const &);
	boost::statechart::result react(message_event const &);
private:
	static sge::log::logger& log();
};

}
}
}

#endif
