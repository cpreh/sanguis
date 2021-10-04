#ifndef SANGUIS_SERVER_STATES_UNPAUSED_HPP_INCLUDED
#define SANGUIS_SERVER_STATES_UNPAUSED_HPP_INCLUDED

#include <sanguis/state_override.hpp>
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
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/list/list10.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/result.hpp>
#include <boost/statechart/state.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis::server::states
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4265)

class unpaused
:
	public
		boost::statechart::state<
			sanguis::server::states::unpaused,
			sanguis::server::states::running
		>
{
	FCPPT_NONMOVABLE(
		unpaused
	);
public:
	using
	reactions
	=
	boost::mpl::list2<
		boost::statechart::custom_reaction<
			sanguis::server::events::tick
		>,
		boost::statechart::custom_reaction<
			sanguis::server::events::message
		>
	>;

	explicit
	unpaused(
		my_context
	);

	~unpaused()
	SANGUIS_STATE_OVERRIDE;

	[[nodiscard]]
	boost::statechart::result
	react(
		sanguis::server::events::tick const &
	);

	[[nodiscard]]
	boost::statechart::result
	react(
		sanguis::server::events::message const &
	);

	[[nodiscard]]
	sanguis::messages::call::result
	operator()(
		sanguis::server::player_id,
		sanguis::messages::client::attack_dest const &
	);

	[[nodiscard]]
	sanguis::messages::call::result
	operator()(
		sanguis::server::player_id,
		sanguis::messages::client::change_world const &
	);

	[[nodiscard]]
	sanguis::messages::call::result
	operator()(
		sanguis::server::player_id,
		sanguis::messages::client::direction const &
	);

	[[nodiscard]]
	sanguis::messages::call::result
	operator()(
		sanguis::server::player_id,
		sanguis::messages::client::drop_or_pickup_weapon const &
	);

	[[nodiscard]]
	sanguis::messages::call::result
	operator()(
		sanguis::server::player_id,
		sanguis::messages::client::reload const &
	);

	[[nodiscard]]
	sanguis::messages::call::result
	operator()(
		sanguis::server::player_id,
		sanguis::messages::client::start_shooting const &
	);

	[[nodiscard]]
	sanguis::messages::call::result
	operator()(
		sanguis::server::player_id,
		sanguis::messages::client::stop_shooting const &
	);

	[[nodiscard]]
	sanguis::messages::call::result
	operator()(
		sanguis::server::player_id,
		sanguis::messages::client::unpause const &
	);

	[[nodiscard]]
	sanguis::messages::call::result
	operator()(
		sanguis::server::player_id,
		sanguis::messages::client::pause const &
	);
private:
	fcppt::log::object log_;

	sanguis::server::net::slowdown slowdown_;
};

FCPPT_PP_POP_WARNING

}

#endif
