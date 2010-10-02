#ifndef SANGUIS_CLIENT_STATES_WAITING_FOR_PLAYER_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_WAITING_FOR_PLAYER_HPP_INCLUDED

#include <boost/statechart/state.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/result.hpp>

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
		boost::statechart::custom_reacton<
			events::message
		>,
		boost::statechart::custom_reacton<
			events::player_action
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
		events::player_action const &
	);

	boost::statechart::result
	operator()(
		messages::add_own_player const &
	);
};

}
}
}

#endif
