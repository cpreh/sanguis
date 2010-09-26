#ifndef SANGUIS_CLIENT_STATES_INGAME_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_INGAME_HPP_INCLUDED

#include "running.hpp"
#include "../events/menu_fwd.hpp"
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
		running
	>
{
public:
	typedef boost::mpl::list<
		boost::statechart::custom_reaction<
			events::menu
		>
	> reactions;

	explicit ingame(
		my_context
	);

	typedef boost::statechart::result result_type;

	boost::statechart::result
	react(
		events::menu const &
	);
};

}
}
}

#endif
