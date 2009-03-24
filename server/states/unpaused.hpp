#ifndef SANGUIS_SERVER_STATES_UNPAUSED_HPP_INCLUDED
#define SANGUIS_SERVER_STATES_UNPAUSED_HPP_INCLUDED

#include "../message_event_fwd.hpp"
#include "../environment_fwd.hpp"
#include "running.hpp"
#include "../../messages/fwd.hpp"
#include "../../net/types.hpp"
#include <sge/time/timer.hpp>
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

class unpaused
	: public boost::statechart::simple_state<unpaused,running>
{
	public:
	typedef boost::mpl::list<
		boost::statechart::custom_reaction<
			tick_event
		>,
		boost::statechart::custom_reaction<
			message_event
		> 
	> reactions;
	
	unpaused();

	void add_enemy();

	boost::statechart::result
	react(
		tick_event const &);

	boost::statechart::result
	react(
		message_event const &);

	boost::statechart::result
	operator()(
		net::id_type,
		messages::player_direction const &);
	
	boost::statechart::result
	operator()(
		net::id_type,
		messages::player_rotation const &);
	
	boost::statechart::result
	operator()(
		net::id_type,
		messages::player_start_shooting const &);
	
	boost::statechart::result
	operator()(
		net::id_type,
		messages::player_stop_shooting const &);
	
	boost::statechart::result
	operator()(
		net::id_type,
		messages::player_change_weapon const &);

	boost::statechart::result
	operator()(
		net::id_type,
		messages::player_unpause const &);

	boost::statechart::result
	operator()(
		net::id_type,
		messages::player_pause const &);

	boost::statechart::result
	operator()(
		net::id_type,
		messages::disconnect const &);
private:
	boost::statechart::result
	handle_default_msg(
		net::id_type,
		messages::base const &);
	
	server::environment const environment();
	void send(
		messages::auto_ptr);
	
	static sge::log::logger &log();

	sge::time::timer send_timer;
};

}
}
}

#endif
