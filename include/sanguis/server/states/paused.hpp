#ifndef SANGUIS_SERVER_STATES_PAUSED_HPP_INCLUDED
#define SANGUIS_SERVER_STATES_PAUSED_HPP_INCLUDED

#include <sanguis/server/player_id.hpp>
#include <sanguis/server/events/message_fwd.hpp>
#include <sanguis/server/states/running.hpp>
#include <sanguis/messages/client/base_fwd.hpp>
#include <sanguis/messages/client/pause_fwd.hpp>
#include <sanguis/messages/client/unpause_fwd.hpp>
#include <fcppt/noncopyable.hpp>
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

class paused
:
	public boost::statechart::simple_state<
		sanguis::server::states::paused,
		sanguis::server::states::running
	>
{
	FCPPT_NONCOPYABLE(
		paused
	);
public:
	typedef boost::mpl::list1<
		boost::statechart::custom_reaction<
			sanguis::server::events::message
		>
	> reactions;

	paused();

	virtual
	~paused();

	// reactions
	boost::statechart::result
	react(
		sanguis::server::events::message const &
	);

	boost::statechart::result
	operator()(
		sanguis::server::player_id,
		sanguis::messages::client::unpause const &
	);

	boost::statechart::result
	operator()(
		sanguis::server::player_id,
		sanguis::messages::client::pause const &
	);
private:
	boost::statechart::result
	handle_default_msg(
		sanguis::server::player_id,
		sanguis::messages::client::base const &
	);
};

}
}
}

#endif
