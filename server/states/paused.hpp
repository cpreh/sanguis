#ifndef SANGUIS_SERVER_STATES_PAUSED_HPP_INCLUDED
#define SANGUIS_SERVER_STATES_PAUSED_HPP_INCLUDED

#include "running.hpp"
#include "../environment_fwd.hpp"
#include "../../messages/player_unpause.hpp"
#include "../../messages/player_pause.hpp"
#include "../../messages/disconnect.hpp"
#include "../../messages/base_fwd.hpp"
#include "../../net/id_type.hpp"
#include <sge/log/logger_fwd.hpp>
#include <boost/mpl/list.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/result.hpp>
#include <boost/statechart/custom_reaction.hpp>

namespace sanguis
{
namespace server
{
namespace states
{

class paused
	: public boost::statechart::simple_state<paused,running>
{
public:
	typedef boost::mpl::list<
		boost::statechart::custom_reaction<tick_event>,
		boost::statechart::custom_reaction<message_event> 
	> reactions;
	
	// reactions
	boost::statechart::result react(tick_event const &);
	boost::statechart::result react(message_event const &);

	boost::statechart::result
	operator()(
		net::id_type,
		messages::disconnect const &);

	boost::statechart::result
	operator()(
		net::id_type,
		messages::player_unpause const &);
	
	boost::statechart::result
	operator()(
		net::id_type,
		messages::player_pause const &);
private:
	boost::statechart::result handle_default_msg(
		net::id_type,
		messages::base const &);

	static sge::log::logger &log();
};

}
}
}

#endif
