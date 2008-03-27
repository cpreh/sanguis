#ifndef SANGUIS_CLIENT_RUNNING_STATE_HPP_INCLUDED
#define SANGUIS_CLIENT_RUNNING_STATE_HPP_INCLUDED

#include "../tick_event.hpp"
#include "../messages/fwd.hpp"
#include "../messages/entity_message.hpp"
#include "../draw/scene_drawer.hpp"
#include "message_event.hpp"
#include "machine.hpp"
#include "input_handler.hpp"
#include <sge/math/vector.hpp>
#include <sge/scoped_connection.hpp>
#include <boost/statechart/state.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/result.hpp>
#include <boost/mpl/list.hpp>

namespace sanguis
{
namespace draw
{
class player;
}

namespace client
{

struct player_action;

struct running_state 
	: public boost::statechart::state<running_state,machine>
{
	typedef boost::mpl::list<
		boost::statechart::custom_reaction<tick_event>,
		boost::statechart::custom_reaction<message_event>
		> reactions;

	running_state(my_context);
	boost::statechart::result react(const tick_event &);
	boost::statechart::result react(const message_event &);
	
	boost::statechart::result operator()(const messages::disconnect&);
	boost::statechart::result operator()(const messages::game_state&);
private:
	boost::statechart::result handle_default_msg(const messages::base&);
	void handle_player_action(const player_action&);
	void handle_direction(const draw::player&, const player_action&);
	void handle_rotation(const draw::player&, const player_action&);

	draw::scene_drawer     drawer;
	sge::math::vector2     direction;
	sge::sprite::point     cursor_pos;
	input_handler          input;
	sge::scoped_connection input_connection;
	entity_id              cursor_id;
};
}
}

#endif
