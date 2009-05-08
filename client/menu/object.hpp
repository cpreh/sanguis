#ifndef SANGUIS_CLIENT_MENU_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_MENU_OBJECT_HPP_INCLUDED

#include "callbacks/object.hpp"
#include "menus/main.hpp"
#include "menus/connect.hpp"
#include "menus/connect_box.hpp"
#include "button.hpp"
#include "mover.hpp"
#include "../cursor.hpp"
#include "../../time_type.hpp"
#include <sge/systems/instance_fwd.hpp>
#include <sge/filesystem/path.hpp>
#include <sge/gui/widgets/buttons/text.hpp>
#include <sge/gui/widgets/backdrop.hpp>
#include <sge/gui/widgets/graphics.hpp>
#include <sge/gui/widgets/edit.hpp>
#include <sge/gui/widgets/label.hpp>
#include <sge/gui/manager.hpp>
#include <sge/signal/connection_manager.hpp>
#include <sge/noncopyable.hpp>
#include <sge/string.hpp>

#include <sge/sprite/system.hpp>
#include <sge/sprite/object.hpp>

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
		sge::systems::instance const &,
		callbacks::object const &);
	void process(
		time_type);
	void connection_error(
		sge::string const &message);
private:
	sge::systems::instance const &sys_;
	
	sge::filesystem::path const 
		menu_path,
		buttons_path,
		labels_path;

	sge::gui::manager m;

	menus::main main_;
	menus::connect connect_;
	menus::connect_box connect_box_;
	
	mover mover_;
	sge::signal::connection_manager connections_;
	callbacks::object const callbacks_;
	sge::sprite::system ss;
	sge::sprite::object const background;

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
