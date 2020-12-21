#ifndef SANGUIS_CLIENT_STATES_WAITING_FOR_PLAYER_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_WAITING_FOR_PLAYER_HPP_INCLUDED

#include <sanguis/state_override.hpp>
#include <sanguis/client/events/action_fwd.hpp>
#include <sanguis/client/events/message_fwd.hpp>
#include <sanguis/client/states/running.hpp>
#include <sanguis/messages/call/result_fwd.hpp>
#include <sanguis/messages/server/add_own_player_fwd.hpp>
#include <fcppt/nonmovable.hpp>
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

class waiting_for_player
:
	public boost::statechart::state<
		sanguis::client::states::waiting_for_player,
		sanguis::client::states::running
	>
{
	FCPPT_NONMOVABLE(
		waiting_for_player
	);
public:
	using
	reactions
	=
	boost::mpl::list2<
		boost::statechart::custom_reaction<
			sanguis::client::events::message
		>,
		boost::statechart::custom_reaction<
			sanguis::client::events::action
		>
	>;

	explicit
	waiting_for_player(
		my_context
	);

	~waiting_for_player()
	SANGUIS_STATE_OVERRIDE;

	[[nodiscard]]
	boost::statechart::result
	react(
		sanguis::client::events::message const &
	);

	[[nodiscard]]
	boost::statechart::result
	react(
		sanguis::client::events::action const &
	);

	using
	result_type
	=
	sanguis::messages::call::result;

	[[nodiscard]]
	sanguis::messages::call::result
	operator()(
		sanguis::messages::server::add_own_player const &
	);
private:
	fcppt::log::object log_;
};

FCPPT_PP_POP_WARNING

}
}
}

#endif
