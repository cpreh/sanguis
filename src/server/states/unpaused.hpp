#ifndef SANGUIS_SERVER_STATES_UNPAUSED_HPP_INCLUDED
#define SANGUIS_SERVER_STATES_UNPAUSED_HPP_INCLUDED

#include "../message_event_fwd.hpp"
#include "../../messages/player_attack_dest.hpp"
#include "../../messages/player_direction.hpp"
#include "../../messages/player_rotation.hpp"
#include "../../messages/player_start_shooting.hpp"
#include "../../messages/player_stop_shooting.hpp"
#include "../../messages/player_change_weapon.hpp"
#include "../../messages/player_pause.hpp"
#include "../../messages/player_unpause.hpp"
#include "../../messages/disconnect.hpp"
#include "../../messages/base_fwd.hpp"
#include "../../net/id.hpp"
#include "running.hpp"
#include <fcppt/log/object_fwd.hpp>
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
:
	public boost::statechart::simple_state<
		unpaused,
		running
	>
{
	FCPPT_NONCOPYABLE(
		unpaused
	);
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

	~unpaused();

	boost::statechart::result
	react(
		tick_event const &
	);

	boost::statechart::result
	react(
		message_event const &
	);

	boost::statechart::result
	operator()(
		net::id,
		messages::player_attack_dest const &
	);

	boost::statechart::result
	operator()(
		net::id,
		messages::player_direction const &
	);
	
	boost::statechart::result
	operator()(
		net::id,
		messages::player_rotation const &
	);
	
	boost::statechart::result
	operator()(
		net::id,
		messages::player_start_shooting const &
	);
	
	boost::statechart::result
	operator()(
		net::id,
		messages::player_stop_shooting const &
	);
	
	boost::statechart::result
	operator()(
		net::id,
		messages::player_change_weapon const &
	);

	boost::statechart::result
	operator()(
		net::id,
		messages::player_unpause const &
	);

	boost::statechart::result
	operator()(
		net::id,
		messages::player_pause const &
	);
private:
	boost::statechart::result
	handle_default_msg(
		net::id,
		messages::base const &
	);
	
	static fcppt::log::object &
	log();
};

}
}
}

#endif
