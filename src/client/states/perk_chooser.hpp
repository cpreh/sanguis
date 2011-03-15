#ifndef SANGUIS_CLIENT_STATES_PERK_CHOOSER_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_PERK_CHOOSER_HPP_INCLUDED

#include "has_player.hpp"
#include "../gui/perk/activation.hpp"
#include "../events/action_fwd.hpp"
#include "../events/tick_fwd.hpp"
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

class perk_chooser
:
	public boost::statechart::state<
		perk_chooser,
		has_player
	>
{
	FCPPT_NONCOPYABLE(
		perk_chooser
	);
public:
	typedef boost::mpl::list<
		boost::statechart::custom_reaction<
			events::tick
		>,
		boost::statechart::custom_reaction<
			events::action
		>
	> reactions;

	explicit perk_chooser(
		my_context
	);

	~perk_chooser();

	typedef boost::statechart::result result_type;

	boost::statechart::result
	react(
		events::tick const &
	);

	boost::statechart::result
	react(
		events::action const &
	);
private:
	client::gui::perk::activation chooser_activation_;
};

}
}
}

#endif
