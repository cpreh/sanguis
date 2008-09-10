#ifndef SANGUIS_CLIENT_CONNECTING_STATE_HPP_INCLUDED
#define SANGUIS_CLIENT_CONNECTING_STATE_HPP_INCLUDED

#include "message_event.hpp"
#include "machine.hpp"
#include "../tick_event.hpp"
#include "../messages/fwd.hpp"
#include <sge/log/fwd.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/mpl/list.hpp>

namespace sanguis
{
namespace client
{
struct connecting_state 
	: public boost::statechart::simple_state<connecting_state,machine>
{
	typedef boost::mpl::list<
		boost::statechart::custom_reaction<tick_event>,
		boost::statechart::custom_reaction<message_event> 
		> reactions;

	bool connected;

	connecting_state();
	boost::statechart::result react(message_event const &);
	boost::statechart::result react(tick_event const &);

	boost::statechart::result operator()(messages::disconnect const &);
	boost::statechart::result operator()(messages::assign_id const &);
	boost::statechart::result operator()(messages::connect const &);
private:
	boost::statechart::result handle_default_msg(messages::base const &);
	static sge::log::logger &log();
};
}
}

#endif
