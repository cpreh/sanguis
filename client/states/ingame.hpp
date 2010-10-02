#ifndef SANGUIS_CLIENT_STATES_INGAME_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_INGAME_HPP_INCLUDED

#include "has_player.hpp"
#include "../events/player_action_fwd.hpp"
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

class ingame
:
	public boost::statechart::state<
		ingame,
		has_player	
	>
{
	FCPPT_NONCOPYABLE(
		ingame
	)
public:
	typedef boost::mpl::list<
		boost::statechart::custom_reaction<
			events::player_action
		>
	> reactions;

	explicit ingame(
		my_context
	);

	~ingame();

	typedef boost::statechart::result result_type;

	boost::statechart::result
	react(
		events::player_action const &
	);
};

}
}
}

#endif
