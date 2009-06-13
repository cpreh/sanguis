#ifndef SANGUIS_CLIENT_STATES_GAMEOVER_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_GAMEOVER_HPP_INCLUDED

#include "running.hpp"
#include "../menu_event.hpp"
#include "../message_event_fwd.hpp"
#include "../../messages/unpause.hpp"
#include "../../tick_event_fwd.hpp"
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
	: public boost::statechart::state<gameover,machine>
{
public:
	typedef boost::mpl::list<
		boost::statechart::custom_reaction<tick_event>,
		boost::statechart::custom_reaction<message_event>,
		boost::statechart::custom_reaction<menu_event>
	> reactions;

	gameover(my_context);

	boost::statechart::result react(tick_event const &);
	boost::statechart::result react(message_event const &);
	boost::statechart::result react(menu_event const &);

	private:
	boost::statechart::result handle_default_msg(messages::base const &);
	void return_clicked();

	sge::gui::manager m_;
	sge::gui::widgets::backdrop background_;
		sge::gui::widgets::label dead_label;
		sge::gui::widgets::base score;
			sge::gui::widgets::label names_head;
			sge::gui::widgets::label score_head;
			sge::gui::widgets::label names_text;
			sge::gui::widgets::label score_text;
		sge::gui::widgets::buttons::text buttons_return;
	sge::signal::scoped_connection return_connection;

};
}
}
}

#endif
