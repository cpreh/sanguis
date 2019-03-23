#ifndef SANGUIS_SERVER_STATES_UNPAUSED_HPP_INCLUDED
#define SANGUIS_SERVER_STATES_UNPAUSED_HPP_INCLUDED

#include <sanguis/messages/call/result_fwd.hpp>
#include <sanguis/messages/client/attack_dest_fwd.hpp>
#include <sanguis/messages/client/change_world_fwd.hpp>
#include <sanguis/messages/client/direction_fwd.hpp>
#include <sanguis/messages/client/drop_or_pickup_weapon_fwd.hpp>
#include <sanguis/messages/client/pause_fwd.hpp>
#include <sanguis/messages/client/reload_fwd.hpp>
#include <sanguis/messages/client/start_shooting_fwd.hpp>
#include <sanguis/messages/client/stop_shooting_fwd.hpp>
#include <sanguis/messages/client/unpause_fwd.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/events/message_fwd.hpp>
#include <sanguis/server/events/tick_fwd.hpp>
#include <sanguis/server/net/slowdown.hpp>
#include <sanguis/server/states/running.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/list/list10.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/result.hpp>
#include <boost/statechart/state.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace states
{

class unpaused
:
	public
		boost::statechart::state<
			sanguis::server::states::unpaused,
			sanguis::server::states::running
		>
{
	FCPPT_NONCOPYABLE(
		unpaused
	);
public:
	typedef
	boost::mpl::list2<
		boost::statechart::custom_reaction<
			sanguis::server::events::tick
		>,
		boost::statechart::custom_reaction<
			sanguis::server::events::message
		>
	>
	reactions;

	explicit
	unpaused(
		my_context
	);

	~unpaused();

	boost::statechart::result
	react(
		sanguis::server::events::tick const &
	);

	boost::statechart::result
	react(
		sanguis::server::events::message const &
	);

	sanguis::messages::call::result
	operator()(
		sanguis::server::player_id,
		sanguis::messages::client::attack_dest const &
	);

	sanguis::messages::call::result
	operator()(
		sanguis::server::player_id,
		sanguis::messages::client::change_world const &
	);

	sanguis::messages::call::result
	operator()(
		sanguis::server::player_id,
		sanguis::messages::client::direction const &
	);

	sanguis::messages::call::result
	operator()(
		sanguis::server::player_id,
		sanguis::messages::client::drop_or_pickup_weapon const &
	);

	sanguis::messages::call::result
	operator()(
		sanguis::server::player_id,
		sanguis::messages::client::reload const &
	);

	sanguis::messages::call::result
	operator()(
		sanguis::server::player_id,
		sanguis::messages::client::start_shooting const &
	);

	sanguis::messages::call::result
	operator()(
		sanguis::server::player_id,
		sanguis::messages::client::stop_shooting const &
	);

	sanguis::messages::call::result
	operator()(
		sanguis::server::player_id,
		sanguis::messages::client::unpause const &
	);

	sanguis::messages::call::result
	operator()(
		sanguis::server::player_id,
		sanguis::messages::client::pause const &
	);
private:
	fcppt::log::object log_;

	sanguis::server::net::slowdown slowdown_;
};

}
}
}

#endif
