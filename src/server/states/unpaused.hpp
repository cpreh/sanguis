#ifndef SANGUIS_SERVER_STATES_UNPAUSED_HPP_INCLUDED
#define SANGUIS_SERVER_STATES_UNPAUSED_HPP_INCLUDED

#include "running.hpp"
#include "../events/message_fwd.hpp"
#include "../events/tick_fwd.hpp"
#include "../player_id.hpp"
#include "../../messages/player_attack_dest.hpp"
#include "../../messages/player_direction.hpp"
#include "../../messages/player_start_shooting.hpp"
#include "../../messages/player_stop_shooting.hpp"
#include "../../messages/player_change_weapon.hpp"
#include "../../messages/player_pause.hpp"
#include "../../messages/player_unpause.hpp"
#include "../../messages/base_fwd.hpp"
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
			events::tick
		>,
		boost::statechart::custom_reaction<
			events::message
		>
	> reactions;

	unpaused();

	~unpaused();

	boost::statechart::result
	react(
		events::tick const &
	);

	boost::statechart::result
	react(
		events::message const &
	);

	boost::statechart::result
	operator()(
		server::player_id,
		messages::player_attack_dest const &
	);

	boost::statechart::result
	operator()(
		server::player_id,
		messages::player_direction const &
	);

	boost::statechart::result
	operator()(
		server::player_id,
		messages::player_start_shooting const &
	);

	boost::statechart::result
	operator()(
		server::player_id,
		messages::player_stop_shooting const &
	);

	boost::statechart::result
	operator()(
		server::player_id,
		messages::player_change_weapon const &
	);

	boost::statechart::result
	operator()(
		server::player_id,
		messages::player_unpause const &
	);

	boost::statechart::result
	operator()(
		server::player_id,
		messages::player_pause const &
	);
private:
	boost::statechart::result
	handle_default_msg(
		server::player_id,
		messages::base const &
	);
};

}
}
}

#endif
