#ifndef SANGUIS_SERVER_STATES_UNPAUSED_HPP_INCLUDED
#define SANGUIS_SERVER_STATES_UNPAUSED_HPP_INCLUDED

#include "running.hpp"
#include "../../messages/fwd.hpp"
#include "../../net/types.hpp"
#include "../../console_timer.hpp"
#include <boost/mpl/list.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/result.hpp>
#include <boost/statechart/custom_reaction.hpp>

namespace sanguis
{
namespace server
{

struct message_event;
class environment;

namespace states
{

class unpaused
	: public boost::statechart::simple_state<unpaused,running>
{
	public:
	typedef boost::mpl::list<
		boost::statechart::custom_reaction<tick_event>,
		boost::statechart::custom_reaction<message_event> 
		> reactions;
	
	unpaused();

	void add_enemy();

	// reactions
	boost::statechart::result react(
		tick_event const &);
	boost::statechart::result react(
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
	
	boost::statechart::result operator()(const net::id_type,const messages::player_stop_shooting &);
	boost::statechart::result operator()(const net::id_type,const messages::player_change_weapon &);
	boost::statechart::result operator()(const net::id_type,const messages::player_unpause &);
	boost::statechart::result operator()(const net::id_type,const messages::player_pause &);
	boost::statechart::result operator()(const net::id_type,const messages::disconnect &);
private:
	boost::statechart::result handle_default_msg(const net::id_type,const messages::base &);
	environment const get_environment();
	void send(
		messages::auto_ptr);
	
	static sge::log::logger &log();

	console_timer send_timer;
};

}
}
}

#endif
