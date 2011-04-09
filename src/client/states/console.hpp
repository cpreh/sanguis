#ifndef SANGUIS_CLIENT_STATES_CONSOLE_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_CONSOLE_HPP_INCLUDED

#include "has_player.hpp"
#include "../console/activation.hpp"
#include "../events/action_fwd.hpp"
#include <fcppt/noncopyable.hpp>
#include <boost/statechart/state.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/result.hpp>

namespace sanguis
{
namespace client
{
namespace states
{

class console
:
	public boost::statechart::state<
		console,
		has_player
	>
{
	FCPPT_NONCOPYABLE(
		console
	);
public:
	typedef boost::statechart::custom_reaction<
		events::action
	> reactions;

	explicit console(
		my_context
	);

	~console();

	boost::statechart::result
	react(
		events::action const &
	);
private:
	client::console::activation const console_activation_;
};

}
}
}

#endif
