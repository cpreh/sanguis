#ifndef SANGUIS_SERVER_STATES_UNPAUSED_HPP_INCLUDED
#define SANGUIS_SERVER_STATES_UNPAUSED_HPP_INCLUDED

#include <sanguis/server/player_id.hpp>
#include <sanguis/server/events/message_fwd.hpp>
#include <sanguis/server/events/tick_fwd.hpp>
#include <sanguis/server/states/running.hpp>
#include <sanguis/messages/base_fwd.hpp>
#include <sanguis/messages/player_attack_dest_fwd.hpp>
#include <sanguis/messages/player_change_world_fwd.hpp>
#include <sanguis/messages/player_direction_fwd.hpp>
#include <sanguis/messages/player_drop_or_pickup_weapon_fwd.hpp>
#include <sanguis/messages/player_pause_fwd.hpp>
#include <sanguis/messages/player_position_fwd.hpp>
#include <sanguis/messages/player_reload_fwd.hpp>
#include <sanguis/messages/player_start_shooting_fwd.hpp>
#include <sanguis/messages/player_stop_shooting_fwd.hpp>
#include <sanguis/messages/player_unpause_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/list/list10.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/result.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace states
{

class unpaused
:
	public boost::statechart::simple_state<
		sanguis::server::states::unpaused,
		sanguis::server::states::running
	>
{
	FCPPT_NONCOPYABLE(
		unpaused
	);
public:
	typedef boost::mpl::list2<
		boost::statechart::custom_reaction<
			sanguis::server::events::tick
		>,
		boost::statechart::custom_reaction<
			sanguis::server::events::message
		>
	> reactions;

	unpaused();

	virtual
	~unpaused();

	boost::statechart::result
	react(
		sanguis::server::events::tick const &
	);

	boost::statechart::result
	react(
		sanguis::server::events::message const &
	);

	boost::statechart::result
	operator()(
		sanguis::server::player_id,
		sanguis::messages::player_attack_dest const &
	);

	boost::statechart::result
	operator()(
		sanguis::server::player_id,
		sanguis::messages::player_change_world const &
	);

	boost::statechart::result
	operator()(
		sanguis::server::player_id,
		sanguis::messages::player_direction const &
	);

	boost::statechart::result
	operator()(
		sanguis::server::player_id,
		sanguis::messages::player_drop_or_pickup_weapon const &
	);

	boost::statechart::result
	operator()(
		sanguis::server::player_id,
		sanguis::messages::player_position const &
	);

	boost::statechart::result
	operator()(
		sanguis::server::player_id,
		sanguis::messages::player_reload const &
	);

	boost::statechart::result
	operator()(
		sanguis::server::player_id,
		sanguis::messages::player_start_shooting const &
	);

	boost::statechart::result
	operator()(
		sanguis::server::player_id,
		sanguis::messages::player_stop_shooting const &
	);

	boost::statechart::result
	operator()(
		sanguis::server::player_id,
		sanguis::messages::player_unpause const &
	);

	boost::statechart::result
	operator()(
		sanguis::server::player_id,
		sanguis::messages::player_pause const &
	);
private:
	boost::statechart::result
	handle_default_msg(
		sanguis::server::player_id,
		sanguis::messages::base const &
	);
};

}
}
}

#endif
