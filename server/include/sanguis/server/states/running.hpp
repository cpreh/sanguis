#ifndef SANGUIS_SERVER_STATES_RUNNING_HPP_INCLUDED
#define SANGUIS_SERVER_STATES_RUNNING_HPP_INCLUDED

#include <sanguis/state_override.hpp>
#include <sanguis/messages/call/result_fwd.hpp>
#include <sanguis/messages/client/cheat_fwd.hpp>
#include <sanguis/messages/client/choose_perk_fwd.hpp>
#include <sanguis/messages/client/console_command_fwd.hpp>
#include <sanguis/messages/client/info_fwd.hpp>
#include <sanguis/server/console.hpp>
#include <sanguis/server/machine.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/events/disconnect_fwd.hpp>
#include <sanguis/server/events/message_fwd.hpp>
#include <sanguis/server/global/context_fwd.hpp>
#include <sanguis/server/states/unpaused_fwd.hpp>
#include <fcppt/nonmovable.hpp>
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
namespace server
{
namespace states
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4265)

class running
:
	public
		boost::statechart::state<
			sanguis::server::states::running,
			sanguis::server::machine,
			sanguis::server::states::unpaused
		>
{
	FCPPT_NONMOVABLE(
		running
	);
public:
	using
	reactions
	=
	boost::mpl::list2<
		boost::statechart::custom_reaction<
			sanguis::server::events::message
		>,
		boost::statechart::custom_reaction<
			sanguis::server::events::disconnect
		>
	>;

	explicit
	running(
		my_context
	);

	~running()
	SANGUIS_STATE_OVERRIDE;

	[[nodiscard]]
	boost::statechart::result
	react(
		sanguis::server::events::message const &
	);

	[[nodiscard]]
	boost::statechart::result
	react(
		sanguis::server::events::disconnect const &
	);

	[[nodiscard]]
	sanguis::messages::call::result
	operator()(
		sanguis::server::player_id,
		sanguis::messages::client::info const &
	);

	[[nodiscard]]
	sanguis::messages::call::result
	operator()(
		sanguis::server::player_id,
		sanguis::messages::client::console_command const &
	);

	[[nodiscard]]
	sanguis::messages::call::result
	operator()(
		sanguis::server::player_id,
		sanguis::messages::client::cheat const &
	);

	[[nodiscard]]
	sanguis::messages::call::result
	operator()(
		sanguis::server::player_id,
		sanguis::messages::client::choose_perk const &
	);

	[[nodiscard]]
	sanguis::server::global::context &
	global_context();
private:
	fcppt::log::object log_;

	sanguis::server::console console_;

	fcppt::unique_ptr<
		sanguis::server::global::context
	> const global_context_;
};

FCPPT_PP_POP_WARNING

}
}
}

#endif
