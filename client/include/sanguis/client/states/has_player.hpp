#ifndef SANGUIS_CLIENT_STATES_HAS_PLAYER_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_HAS_PLAYER_HPP_INCLUDED

#include <sanguis/perk_type_fwd.hpp>
#include <sanguis/client/control/action_handler_fwd.hpp>
#include <sanguis/client/events/action_fwd.hpp>
#include <sanguis/client/events/message_fwd.hpp>
#include <sanguis/client/events/tick_fwd.hpp>
#include <sanguis/client/perk/state_fwd.hpp>
#include <sanguis/client/states/ingame_fwd.hpp>
#include <sanguis/client/states/running.hpp>
#include <sanguis/messages/call/result_fwd.hpp>
#include <sanguis/messages/server/available_perks_fwd.hpp>
#include <sanguis/messages/server/level_up_fwd.hpp>
#include <sanguis/messages/server/remove_id_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
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


namespace sanguis
{
namespace client
{
namespace states
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4265)

class has_player
:
	public boost::statechart::state<
		sanguis::client::states::has_player,
		sanguis::client::states::running,
		sanguis::client::states::ingame
	>
{
	FCPPT_NONCOPYABLE(
		has_player
	);
public:
	typedef boost::mpl::list3<
		boost::statechart::custom_reaction<
			sanguis::client::events::message
		>,
		boost::statechart::custom_reaction<
			sanguis::client::events::tick
		>,
		boost::statechart::custom_reaction<
			sanguis::client::events::action
		>
	> reactions;

	explicit
	has_player(
		my_context
	);

	~has_player();

	boost::statechart::result
	react(
		sanguis::client::events::message const &
	);

	boost::statechart::result
	react(
		sanguis::client::events::tick const &
	);

	boost::statechart::result
	react(
		sanguis::client::events::action const &
	);

	typedef
	sanguis::messages::call::result
	result_type;

	sanguis::messages::call::result
	operator()(
		sanguis::messages::server::available_perks const &
	);

	sanguis::messages::call::result
	operator()(
		sanguis::messages::server::level_up const &
	);

	sanguis::messages::call::result
	operator()(
		sanguis::messages::server::remove_id const &
	);

	sanguis::client::perk::state &
	perk_state();
private:
	void
	send_perk_choose(
		sanguis::perk_type
	);

	fcppt::log::object log_;

	fcppt::unique_ptr<
		sanguis::client::control::action_handler
	> const action_handler_;

	fcppt::unique_ptr<
		sanguis::client::perk::state
	> const perk_state_;
};

FCPPT_PP_POP_WARNING

}
}
}

#endif

