#ifndef SANGUIS_CLIENT_GUI_MENU_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_MENU_OBJECT_HPP_INCLUDED

#include "callbacks/object.hpp"
#include "../object_fwd.hpp"
#include "../../config/settings/object_fwd.hpp"
#include "../../../time_type.hpp"
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>

namespace sanguis
{
namespace client
{
namespace gui
{
namespace menu
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		config::settings::object &,
		client::gui::object &,
		callbacks::object const &
	);

	~object();

	void
	process(
		time_type
	);

	void
	connection_error(
		fcppt::string const &message
	);
private:
	fcppt::signal::connection_manager connections_;

	callbacks::object const callbacks_;

	fcppt::string 
		connection_host_,
		connection_port_;

	void
	start_server();

	void
	connect_from_menu();

	void
	connect(
		fcppt::string const &,
		fcppt::string const &
	);

	void
	cancel_connect();
};

}
}
}
}

#endif // SANGUIS_CLIENT_MENU_OBJECT_HPP_INCLUDED
