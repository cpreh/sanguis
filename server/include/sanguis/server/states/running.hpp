#ifndef SANGUIS_SERVER_STATES_RUNNING_HPP_INCLUDED
#define SANGUIS_SERVER_STATES_RUNNING_HPP_INCLUDED

#include <sanguis/server/console.hpp>
#include <sanguis/server/machine.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/events/disconnect_fwd.hpp>
#include <sanguis/server/events/message_fwd.hpp>
#include <sanguis/server/global/context_fwd.hpp>
#include <sanguis/server/states/unpaused_fwd.hpp>
#include <sanguis/messages/call/result_fwd.hpp>
#include <sanguis/messages/client/cheat_fwd.hpp>
#include <sanguis/messages/client/choose_perk_fwd.hpp>
#include <sanguis/messages/client/console_command_fwd.hpp>
#include <sanguis/messages/client/info_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/list/list10.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/result.hpp>
#include <boost/statechart/state.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace states
{

class running
:
	public boost::statechart::state<
		sanguis::server::states::running,
		sanguis::server::machine,
		sanguis::server::states::unpaused
>
{
	FCPPT_NONCOPYABLE(
		running
	);
public:
	typedef boost::mpl::list2<
		boost::statechart::custom_reaction<
			sanguis::server::events::message
		>,
		boost::statechart::custom_reaction<
			sanguis::server::events::disconnect
		>
	> reactions;

	explicit
	running(
		my_context
	);

	~running()
	override;

	boost::statechart::result
	react(
		sanguis::server::events::message const &
	);

	boost::statechart::result
	react(
		sanguis::server::events::disconnect const &
	);

	sanguis::messages::call::result
	operator()(
		sanguis::server::player_id,
		sanguis::messages::client::info const &
	);

	sanguis::messages::call::result
	operator()(
		sanguis::server::player_id,
		sanguis::messages::client::console_command const &
	);

	sanguis::messages::call::result
	operator()(
		sanguis::server::player_id,
		sanguis::messages::client::cheat const &
	);

	sanguis::messages::call::result
	operator()(
		sanguis::server::player_id,
		sanguis::messages::client::choose_perk const &
	);

	sanguis::server::global::context &
	global_context();
private:
	sanguis::server::console console_;

	std::unique_ptr<
		sanguis::server::global::context
	> const global_context_;
};

}
}
}

#endif
