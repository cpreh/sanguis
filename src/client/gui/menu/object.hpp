#ifndef SANGUIS_CLIENT_GUI_MENU_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_MENU_OBJECT_HPP_INCLUDED

#include "callbacks/object.hpp"
#include "connection_box_fwd.hpp"
#include "../object_fwd.hpp"
#include "../../config/settings/object_fwd.hpp"
#include "../../../time_type.hpp"
#include <sge/cegui/toolbox/scoped_gui_sheet.hpp>
#include <sge/cegui/toolbox/scoped_layout.hpp>
#include <fcppt/scoped_ptr.hpp>
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

	sge::cegui::toolbox::scoped_gui_sheet const scoped_gui_sheet_;

	CEGUI::Event::ScopedConnection const
		quickstart_connection_,
		quit_connection_,
		connect_connection_;
	
	typedef fcppt::scoped_ptr<
		menu::connection_box
	> scoped_connection_box_ptr;

	scoped_connection_box_ptr connection_box_;

	bool
	handle_quickstart(
		CEGUI::EventArgs const &
	);

	bool
	handle_quit(
		CEGUI::EventArgs const &
	);

	bool
	handle_connect(
		CEGUI::EventArgs const &
	);

	void
	handle_cancel_connect();

	void
	handle_retry_connect();

	void
	do_connect();
};

}
}
}
}

#endif
