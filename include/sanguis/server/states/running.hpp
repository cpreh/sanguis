#ifndef SANGUIS_SERVER_STATES_RUNNING_HPP_INCLUDED
#define SANGUIS_SERVER_STATES_RUNNING_HPP_INCLUDED

#include <sanguis/server/states/unpaused_fwd.hpp>
#include <sanguis/server/events/disconnect_fwd.hpp>
#include <sanguis/server/events/message_fwd.hpp>
#include <sanguis/server/global/context_fwd.hpp>
#include <sanguis/server/machine.hpp>
#include <sanguis/server/console.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/messages/client_info.hpp>
#include <sanguis/messages/console_command.hpp>
#include <sanguis/messages/player_cheat.hpp>
#include <sanguis/messages/player_choose_perk.hpp>
#include <sanguis/messages/base_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/list/list10.hpp>
#include <boost/statechart/state.hpp>
#include <boost/statechart/result.hpp>
#include <boost/statechart/custom_reaction.hpp>
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
		running,
		machine,
		unpaused
>
{
	FCPPT_NONCOPYABLE(
		running
	);
public:
	typedef boost::mpl::list2<
		boost::statechart::custom_reaction<
			events::message
		>,
		boost::statechart::custom_reaction<
			events::disconnect
		>
	> reactions;

	explicit running(
		my_context
	);

	virtual ~running();

	boost::statechart::result
	react(
		events::message const &
	);

	boost::statechart::result
	react(
		events::disconnect const &
	);

	boost::statechart::result
	operator()(
		server::player_id,
		messages::client_info const &
	);

	boost::statechart::result
	operator()(
		server::player_id,
		messages::console_command const &
	);

	boost::statechart::result
	operator()(
		server::player_id,
		messages::player_cheat const &
	);

	boost::statechart::result
	operator()(
		server::player_id,
		messages::player_choose_perk const &
	);

	global::context &
	global_context();
private:
	boost::statechart::result
	handle_default_msg(
		server::player_id,
		messages::base const &
	);

	sanguis::server::console console_;

	fcppt::scoped_ptr<
		global::context
	> global_context_;
};

}
}
}

#endif
