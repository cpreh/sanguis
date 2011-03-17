#ifndef SANGUIS_CLIENT_GUI_MENU_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_MENU_OBJECT_HPP_INCLUDED

#include "callbacks/object.hpp"
#include "../object_fwd.hpp"
#include "../../config/settings/object_fwd.hpp"
#include "../../../time_type.hpp"
#include <sge/cegui/toolbox/scoped_layout.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>
#include <CEGUI/CEGUIEvent.h>

namespace CEGUI
{
class EventArgs;
}

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
	callbacks::object const callbacks_;

	client::gui::object &gui_;

	sge::cegui::toolbox::scoped_layout const scoped_layout_;

	CEGUI::Event::ScopedConnection const
		quickstart_connection_;

	fcppt::string 
		connection_host_,
		connection_port_;

	bool
	quickstart(
		CEGUI::EventArgs const &
	);

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

#endif
