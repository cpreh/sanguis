#ifndef SANGUIS_CLIENT_STATES_GAMEOVER_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_GAMEOVER_HPP_INCLUDED

#include "running.hpp"
#include "args/gameover_fwd.hpp"
#include "../events/menu_fwd.hpp"
#include "../events/message_fwd.hpp"
#include "../events/tick_fwd.hpp"
#include "../../messages/unpause.hpp"
#include <sge/gui/widgets/buttons/image.hpp>
#include <sge/gui/manager.hpp>
#include <sge/gui/widgets/backdrop.hpp>
#include <sge/gui/widgets/label.hpp>
#include <sge/gui/widgets/buttons/text.hpp>
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
class gameover
:
	public boost::statechart::state<
		gameover,
		machine
	>
{
public:
	typedef boost::mpl::list<
		boost::statechart::custom_reaction<
			events::tick
		>,
		boost::statechart::custom_reaction<
			events::message
		>,
		boost::statechart::custom_reaction<
			events::menu
		>
	> reactions;

	explicit gameover(
		my_context,
		args::gameover const &
	);

	boost::statechart::result
	react(
		events::tick const &
	);

	boost::statechart::result
	react(
		events::message const &
	);

	boost::statechart::result
	react(
		events::menu const &
	);
private:
	boost::statechart::result
	handle_default_msg(
		messages::base const &
	);

	void
	return_clicked();

	sge::gui::manager manager_;
	sge::gui::widgets::backdrop background_;
		sge::gui::widgets::label dead_label_;
		sge::gui::widgets::base score_;
			sge::gui::widgets::label names_head_;
			sge::gui::widgets::label score_head_;
			sge::gui::widgets::label names_text_;
			sge::gui::widgets::label score_text_;
		sge::gui::widgets::buttons::text buttons_return_;
	fcppt::signal::scoped_connection return_connection_;

};
}
}
}

#endif