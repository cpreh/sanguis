#ifndef SANGUIS_SERVER_RUNNING_STATE_HPP_INCLUDED
#define SANGUIS_SERVER_RUNNING_STATE_HPP_INCLUDED

#include "machine.hpp"
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

#include <map>

namespace sanguis
{
namespace server
{

struct running_state
	: public boost::statechart::simple_state<running_state,machine>
{
	typedef boost::mpl::list<
		boost::statechart::custom_reaction<tick_event>,
		boost::statechart::custom_reaction<message_event> 
		> reactions;

	struct player_type
	{
		sanguis::entity_id id;
		messages::pos_type pos,speed;
		messages::space_unit angle;
		messages::string name;
		bool shooting;
		sge::shared_ptr<sge::timer> shoot_timer;
	};

	struct bullet_type
	{
		messages::pos_type pos,speed;

		bullet_type() {}
		bullet_type(const messages::pos_type &pos,const messages::pos_type speed) : pos(pos),speed(speed) {}
	};

	typedef std::map<net::id_type,player_type> player_map;
	typedef std::map<sanguis::entity_id,bullet_type> bullet_map;

	sge::con::var<messages::space_unit> player_speed,bullet_speed,bullet_freq;
	player_map players;
	bullet_map bullets;
	sge::timer send_timer;
	sge::con::action_var<sge::space_unit>::type message_freq;

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

	void process_client_info(const message_event &);

	// game functions
	void create_game(const net::id_type,const messages::client_info &);
	void add_bullet(const net::id_type);
	sge::space_unit set_message_freq(const sge::space_unit,const sge::space_unit);
};

}
}

#endif
