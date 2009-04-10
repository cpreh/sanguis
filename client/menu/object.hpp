#ifndef SANGUIS_CLIENT_MENU_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_MENU_OBJECT_HPP_INCLUDED

#include "callbacks/object.hpp"
#include "button.hpp"
#include "mover.hpp"
#include "../../time_type.hpp"
#include <sge/systems/instance_fwd.hpp>
#include <sge/filesystem/path.hpp>
#include <sge/noncopyable.hpp>
#include <sge/gui/widgets/buttons/text.hpp>
#include <sge/gui/widgets/buttons/image.hpp>
#include <sge/gui/widgets/graphics.hpp>
#include <sge/gui/widgets/edit.hpp>
#include <sge/gui/widget.hpp>
#include <sge/gui/manager.hpp>
#include <sge/signal/connection_manager.hpp>
#include <sge/string.hpp>

namespace sanguis
{
namespace client
{
namespace menu
{
class object
{
SGE_NONCOPYABLE(object)
public:
	object(
		sge::systems::instance &
		callbacks::object const &);
	void process(
		time_type);
	void connection_error(
		sge::string const &message);
private:
	sge::systems::instance &sys_;
	
	sge::filesystem::path const 
		menu_path,
		buttons_path,
		labels_path;

	sge::gui::manager m;

	sge::gui::widget main_menu;
		button main_connect;
		button main_start;
		button main_exit;

	sge::gui::widget connect_menu;
		sge::gui::widget connect_host;
			sge::gui::widgets::graphics connect_host_label;
			sge::gui::widgets::edit connect_host_edit;
		sge::gui::widget connect_port;
			sge::gui::widgets::graphics connect_port_label;
			sge::gui::widgets::edit connect_port_edit;
		sge::gui::widget connect_connect_wrapper;
			client::menu::button connect_connect;
		sge::gui::widget connect_return_wrapper;
			client::menu::button connect_return;
	
	// put this in separate structs
	sge::gui::widget mb_connect;
		sge::gui::label mb_connect_label;
		sge::gui::widget mb_connect_buttons;
			sge::gui::widgets::buttons::text mb_connect_buttons_retry;
			sge::gui::widgets::buttons::text mb_connect_buttons_cancel;

	mover mover_;
	sge::signal::connection_manager connections_;
	callbacks::object const callbacks_;

	sge::string 
		connection_host_,
		connection_port_;

	void start_server();
	void connect_from_menu();
	void connect(
		sge::string const &,
		sge::string const &);
	void cancel_connect();
};
}
}
}

#endif // SANGUIS_CLIENT_MENU_OBJECT_HPP_INCLUDED
