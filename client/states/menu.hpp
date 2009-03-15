#ifndef SANGUIS_CLIENT_STATES_MENU_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_MENU_HPP_INCLUDED

#include "menu_mover.hpp"
#include "../machine.hpp"
#include "../../tick_event.hpp"
#include "../message_event.hpp"
#include <sge/log/fwd.hpp>
#include <sge/gui/widget.hpp>
#include <sge/gui/manager.hpp>
#include <sge/gui/widgets/graphics.hpp>
#include <sge/gui/widgets/buttons/image.hpp>
#include <sge/gui/widgets/edit.hpp>
#include <sge/gui/widgets/backdrop.hpp>
#include <sge/filesystem/path.hpp>
#include <sge/signal/auto_connection.hpp>
#include <boost/statechart/state.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/mpl/list.hpp>

//#define SANGUIS_STATES_MENU_DEBUG

namespace sanguis
{
namespace client
{
namespace states
{
class menu 
	: public boost::statechart::state<menu,machine>
{
	public:
	typedef boost::mpl::list<
		boost::statechart::custom_reaction<tick_event>,
		boost::statechart::custom_reaction<message_event>
		> reactions;

	menu(my_context); 
	boost::statechart::result react(tick_event const &);
	boost::statechart::result react(message_event const &);
	private:
	sge::log::logger &log();
	
	sge::filesystem::path const menu_path,buttons_path,labels_path;
	sge::gui::manager m;

	sge::gui::widget main_menu;
		sge::gui::widgets::buttons::image main_connect;
		sge::gui::widgets::buttons::image main_start;
		sge::gui::widgets::buttons::image main_exit;

#ifndef SANGUIS_STATES_MENU_DEBUG
	sge::gui::widget connect_menu;
		sge::gui::widget connect_host;
			sge::gui::widgets::graphics connect_host_label;
			sge::gui::widgets::edit connect_host_edit;
		sge::gui::widget connect_port;
			sge::gui::widgets::graphics connect_port_label;
			sge::gui::widgets::edit connect_port_edit;
		sge::gui::widget connect_connect_wrapper;
			sge::gui::widgets::buttons::image connect_connect;
		sge::gui::widget connect_return_wrapper;
			sge::gui::widgets::buttons::image connect_return;

	menu_mover mover_;

	sge::signal::auto_connection main_connect_conn;
	sge::signal::auto_connection main_start_conn;
	sge::signal::auto_connection main_exit_conn;

	sge::signal::auto_connection connect_connect_conn;
	sge::signal::auto_connection connect_return_conn;
#endif

	bool connect_now;
	// FIXME: replace by boost::lambda expression or something completely different
	void connect();
	void start_server();
};
}
}
}

#endif
