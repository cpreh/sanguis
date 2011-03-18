#ifndef SANGUIS_SERVER_STATES_PAUSED_HPP_INCLUDED
#define SANGUIS_SERVER_STATES_PAUSED_HPP_INCLUDED

#include "running.hpp"
#include "../events/message_fwd.hpp"
#include "../../messages/player_unpause.hpp"
#include "../../messages/player_pause.hpp"
#include "../../messages/base_fwd.hpp"
#include "../../net/id.hpp"
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <boost/mpl/list.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/result.hpp>
#include <boost/statechart/custom_reaction.hpp>

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
	typedef boost::mpl::list<
		boost::statechart::custom_reaction<
			events::message
		>
	> reactions;
	
	paused();

	~paused();

	// reactions
	boost::statechart::result
	react(
		events::message const &
	);

	boost::statechart::result
	operator()(
		net::id,
		messages::player_unpause const &
	);
	
	boost::statechart::result
	operator()(
		net::id,
		messages::player_pause const &
	);
private:
	boost::statechart::result
	handle_default_msg(
		net::id,
		messages::base const &
	);

	static fcppt::log::object &
	log();
};

}
}
}

#endif
