#ifndef SANGUIS_SERVER_STATES_RUNNING_HPP_INCLUDED
#define SANGUIS_SERVER_STATES_RUNNING_HPP_INCLUDED

#include "unpaused_fwd.hpp"
#include "../global/context_fwd.hpp"
#include "../message_event_fwd.hpp"
#include "../machine.hpp"
#include "../console.hpp"
#include "../../messages/disconnect.hpp"
#include "../../messages/client_info.hpp"
#include "../../messages/console_command.hpp"
#include "../../messages/player_cheat.hpp"
#include "../../messages/player_choose_perk.hpp"
#include "../../messages/base_fwd.hpp"
#include "../../net/id.hpp"
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <boost/statechart/state.hpp>
#include <boost/statechart/result.hpp>
#include <boost/statechart/custom_reaction.hpp>

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
	typedef boost::statechart::custom_reaction<
		message_event
	> reactions;

	explicit running(
		my_context
	);

	~running();
	
	boost::statechart::result
	react(
		message_event const &
	);
	
	boost::statechart::result
	operator()(
		net::id,
		messages::client_info const &
	);

	boost::statechart::result
	operator()(
		net::id,
		messages::console_command const &
	);

	boost::statechart::result
	operator()(
		net::id,
		messages::disconnect const &
	);

	boost::statechart::result
	operator()(
		net::id,
		messages::player_cheat const &
	);

	boost::statechart::result
	operator()(
		net::id,
		messages::player_choose_perk const &
	);

	global::context &
	global_context();
private:
	boost::statechart::result
	handle_default_msg(
		net::id,
		messages::base const &
	);

	static fcppt::log::object
	&log();

	sanguis::server::console console_;

	fcppt::scoped_ptr<
		global::context
	> global_context_;
};

}
}
}

#endif
