#ifndef SANGUIS_CLIENT_STATES_WAITING_FOR_PLAYER_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_WAITING_FOR_PLAYER_HPP_INCLUDED

#include "running.hpp"
#include "../events/message_fwd.hpp"
#include "../events/action_fwd.hpp"
#include "../../messages/add_own_player.hpp"
#include "../../messages/base_fwd.hpp"
#include <fcppt/noncopyable.hpp>
#include <boost/statechart/state.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/result.hpp>
#include <boost/mpl/list.hpp>

namespace sanguis
{
namespace client
{
namespace states
{

class waiting_for_player
:
	public boost::statechart::state<
		waiting_for_player,
		running
	>
{
	FCPPT_NONCOPYABLE(
		waiting_for_player
	)
public:
	typedef boost::mpl::list<
		boost::statechart::custom_reaction<
			events::message
		>,
		boost::statechart::custom_reaction<
			events::action
		>
	> reactions;

	explicit waiting_for_player(
		my_context
	);

	~waiting_for_player();

	boost::statechart::result
	react(
		events::message const &
	);

	boost::statechart::result
	react(
		events::action const &
	);

	typedef boost::statechart::result result_type;

	result_type
	operator()(
		messages::add_own_player const &
	);
private:
	boost::statechart::result
	handle_default_msg(
		sanguis::messages::base const &
	);
};

}
}
}

#endif
