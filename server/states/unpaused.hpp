#ifndef SANGUIS_SERVER_STATES_UNPAUSED_HPP_INCLUDED
#define SANGUIS_SERVER_STATES_UNPAUSED_HPP_INCLUDED

#include "running.hpp"

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
		boost::statechart::custom_reaction<tick_event>,
		boost::statechart::custom_reaction<message_event> 
		> reactions;
	
	unpaused();

	void add_enemy();
	void create_game(const net::id_type,const messages::client_info &);
	bool aborted() const;

	// reactions
	boost::statechart::result react(const tick_event&);
	boost::statechart::result react(const message_event&);

	boost::statechart::result operator()(const net::id_type,const messages::client_info &);
	boost::statechart::result operator()(const net::id_type,const messages::player_direction &);
	boost::statechart::result operator()(const net::id_type,const messages::player_rotation &);
	boost::statechart::result operator()(const net::id_type,const messages::player_start_shooting &);
	boost::statechart::result operator()(const net::id_type,const messages::player_stop_shooting &);
	boost::statechart::result operator()(const net::id_type,const messages::player_change_weapon &);
	boost::statechart::result operator()(const net::id_type,const messages::disconnect &);
	boost::statechart::result handle_default_msg(const net::id_type,const messages::base &);

	void divide_exp(const messages::exp_type);
	void level_callback(entities::player &,const messages::level_type);

	void get_player_exp(const sge::con::arg_list &);

	environment get_environment();
	private:
	console_timer send_timer;
};

}
}
}

#endif
