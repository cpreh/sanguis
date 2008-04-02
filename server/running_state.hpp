#ifndef SANGUIS_SERVER_RUNNING_STATE_HPP_INCLUDED
#define SANGUIS_SERVER_RUNNING_STATE_HPP_INCLUDED

#include "machine.hpp"
#include "entity.hpp"
#include "message_event.hpp"
#include "../tick_event.hpp"
#include "../entity_id.hpp"
#include "../messages/fwd.hpp"
#include "../messages/types.hpp"

#include <sge/string.hpp>
#include <sge/su.hpp>
#include <sge/timer.hpp>
#include <sge/type_info.hpp>
#include <sge/su.hpp>
#include <sge/console/console.hpp>
#include <sge/math/vector.hpp>
#include <sge/math/dim.hpp>

#include <boost/mpl/list.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/result.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/function.hpp>

#include <boost/ptr_container/ptr_map.hpp>

namespace sanguis
{
namespace server
{

class player;

class running_state
	: public boost::statechart::simple_state<running_state,machine>
{
	public:
	typedef boost::mpl::list<
		boost::statechart::custom_reaction<tick_event>,
		boost::statechart::custom_reaction<message_event> 
		> reactions;

	running_state();
	
	// statechart stuff
	boost::statechart::result react(const tick_event&);
	boost::statechart::result react(const message_event&);

	boost::statechart::result operator()(const net::id_type,const messages::client_info &);
	boost::statechart::result operator()(const net::id_type,const messages::disconnect &);
	boost::statechart::result handle_default_msg(const net::id_type,const messages::base &);

	boost::statechart::result operator()(const net::id_type,const messages::player_direction_event &);
	boost::statechart::result operator()(const net::id_type,const messages::player_rotation_event &);

	boost::statechart::result operator()(const net::id_type,const messages::player_start_shooting &);
	boost::statechart::result operator()(const net::id_type,const messages::player_stop_shooting &);

	private:
	typedef boost::ptr_map<entity_id,server::entity> entity_map;

	// game functions
	void create_game(const net::id_type,const messages::client_info &);
	void add_bullet();
	sge::space_unit set_message_freq(const sge::space_unit,const sge::space_unit);
	entity &insert_entity(const entity_id,entity *);

	entity_map entities;

	player *player_;

	sge::timer send_timer;
	sge::con::action_var<sge::space_unit>::type message_freq;
};

}
}

#endif
