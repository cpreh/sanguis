#ifndef SANGUIS_SERVER_STATES_WAITING_HPP_INCLUDED
#define SANGUIS_SERVER_STATES_WAITING_HPP_INCLUDED

#include "../machine.hpp"
#include "../message_event.hpp"
#include "../../tick_event.hpp"
#include "../../messages/connect.hpp"
#include "../../messages/disconnect.hpp"
#include "../../messages/client_info.hpp"
#include "../../messages/base_fwd.hpp"
#include <sge/log/fwd.hpp>
#include <boost/mpl/list.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/result.hpp>

namespace sanguis
{
namespace server
{
namespace states
{
struct waiting
	: public boost::statechart::simple_state<waiting,machine>
{
	typedef boost::mpl::list<
		boost::statechart::custom_reaction<tick_event>,
		boost::statechart::custom_reaction<message_event> 
	> reactions;

	waiting();
	boost::statechart::result react(tick_event const &);
	boost::statechart::result react(message_event const &);

	boost::statechart::result operator()(net::id_type, messages::connect const &);
	boost::statechart::result operator()(net::id_type, messages::disconnect const &);
	boost::statechart::result operator()(net::id_type, messages::client_info const &);
private:
	boost::statechart::result handle_default_msg(net::id_type, messages::base const &);

	static sge::log::logger &log();
};

}
}
}

#endif
