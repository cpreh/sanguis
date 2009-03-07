#ifndef SANGUIS_CLIENT_STATES_INTERMEDIATE_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_INTERMEDIATE_HPP_INCLUDED

#include "menu_mover.hpp"
#include "../machine.hpp"
#include "../../tick_event.hpp"
#include "../message_event.hpp"
#include <sge/log/fwd.hpp>
#include <sge/gui/widget.hpp>
#include <sge/gui/manager.hpp>
#include <sge/gui/widgets/label.hpp>
#include <sge/gui/widgets/edit.hpp>
#include <sge/gui/widgets/button.hpp>
#include <sge/signals/connection.hpp>
#include <boost/statechart/state.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/mpl/list.hpp>

namespace sanguis
{
namespace client
{
namespace states
{
class intermediate 
	: public boost::statechart::state<intermediate,machine>
{
	public:
	typedef boost::mpl::list<
		boost::statechart::custom_reaction<tick_event>,
		boost::statechart::custom_reaction<message_event>
		> reactions;

	intermediate(my_context); 
	boost::statechart::result react(tick_event const &);
	boost::statechart::result react(message_event const &);
	private:
	sge::log::logger &log();
	
	sge::gui::manager m;
	sge::gui::widget top;
	sge::gui::widget host;
	sge::gui::widgets::label host_label;
	sge::gui::widgets::edit host_edit;
	sge::gui::widget port;
	sge::gui::widgets::label port_label;
	sge::gui::widgets::edit port_edit;
	sge::gui::widgets::button connect_;
	sge::gui::widgets::button return_menu;
	sge::gui::widget main_menu;
	sge::gui::widgets::button menu_connect;
	sge::gui::widgets::button menu_start;
	sge::gui::widgets::button menu_exit;
	menu_mover mover_;
	sge::signals::connection connect_to_server_menu;
	sge::signals::connection return_to_main_menu;
	sge::signals::connection connect_clicked;
	sge::signals::connection start_server_clicked;
	sge::signals::connection menu_exit_clicked;

	bool connect_now;
	// FIXME: replace by boost::lambda expression or something completely different
	void connect();
	void start_server();
};
}
}
}

#endif
