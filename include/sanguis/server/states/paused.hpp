#ifndef SANGUIS_SERVER_STATES_PAUSED_HPP_INCLUDED
#define SANGUIS_SERVER_STATES_PAUSED_HPP_INCLUDED

#include <sanguis/server/states/running.hpp>
#include <sanguis/server/events/message_fwd.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/messages/player_unpause.hpp>
#include <sanguis/messages/player_pause.hpp>
#include <sanguis/messages/base_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/list/list10.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/result.hpp>
#include <boost/statechart/custom_reaction.hpp>
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
		paused,
		running
	>
{
	FCPPT_NONCOPYABLE(
		paused
	);
public:
	typedef boost::mpl::list1<
		boost::statechart::custom_reaction<
			events::message
		>
	> reactions;

	paused();

	virtual ~paused();

	// reactions
	boost::statechart::result
	react(
		events::message const &
	);

	boost::statechart::result
	operator()(
		server::player_id,
		messages::player_unpause const &
	);

	boost::statechart::result
	operator()(
		server::player_id,
		messages::player_pause const &
	);
private:
	boost::statechart::result
	handle_default_msg(
		server::player_id,
		messages::base const &
	);
};

}
}
}

#endif
