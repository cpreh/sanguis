#ifndef SANGUIS_CLIENT_STATES_PERK_CHOOSER_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_PERK_CHOOSER_HPP_INCLUDED

#include "has_player.hpp"
#include "../scoped_pause.hpp"
#include "../gui/perk/chooser.hpp"
#include "../events/action_fwd.hpp"
#include "../events/overlay_fwd.hpp"
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
	typedef boost::mpl::list3<
		boost::statechart::custom_reaction<
			events::action
		>,
		boost::statechart::custom_reaction<
			events::overlay
		>,
		boost::statechart::custom_reaction<
			events::tick
		>
	> reactions;

	explicit perk_chooser(
		my_context
	);

	~perk_chooser();

	boost::statechart::result
	react(
		events::action const &
	);

	boost::statechart::result
	react(
		events::overlay const &
	);

	boost::statechart::result
	react(
		events::tick const &
	);
private:
	client::scoped_pause const pause_;

	client::gui::perk::chooser perk_chooser_gui_;
};

}
}
}

#endif
