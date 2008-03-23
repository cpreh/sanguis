#ifndef SANGUIS_SERVER_RUNNING_STATE_HPP_INCLUDED
#define SANGUIS_SERVER_RUNNING_STATE_HPP_INCLUDED

#include "machine.hpp"
#include "message_event.hpp"
#include "../tick_event.hpp"
#include "../entity_id.hpp"
#include "../messages/fwd.hpp"

#include <sge/string.hpp>
#include <sge/timer.hpp>
#include <sge/type_info.hpp>
#include <sge/types.hpp>
#include <sge/console/console.hpp>
#include <sge/math/vector.hpp>
#include <sge/math/dim.hpp>

#include <boost/mpl/list.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/result.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/function.hpp>

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
		sge::math::vector2 pos,speed;
		sge::math::dim2 dim;
		sge::space_unit angle;
		sge::string name;
	};

	//::sanguis::entity_id id_counter;
	player_type player;
	sge::timer send_timer;
	sge::con::var<sge::space_unit> player_speed;

	running_state();
	
	// statechart stuff
	boost::statechart::result react(const tick_event&);
	boost::statechart::result react(const message_event&);

	boost::statechart::result operator()(const net::id_type,const messages::client_info &);
	boost::statechart::result operator()(const net::id_type,const messages::disconnect &);
	boost::statechart::result handle_default_msg(const net::id_type,const messages::base &);

	boost::statechart::result operator()(const net::id_type,const messages::player_direction_event &);
	boost::statechart::result operator()(const net::id_type,const messages::player_rotation_event &);

	// game functions
	void create_game(const messages::client_info &);
};

}
}

#endif
