#ifndef SANGUIS_CLIENT_GUI_MENU_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_MENU_OBJECT_HPP_INCLUDED

#include <sanguis/client/gui/menu/callbacks/object.hpp>
#include <sanguis/client/gui/menu/connection_box_fwd.hpp>
#include <sanguis/client/gui/object_fwd.hpp>
#include <sanguis/client/config/settings/object_fwd.hpp>
#include <sanguis/duration.hpp>
#include <sge/cegui/toolbox/scoped_gui_sheet.hpp>
#include <sge/cegui/toolbox/scoped_layout.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Event.h>
#include <fcppt/config/external_end.hpp>


namespace CEGUI
{
class EventArgs;
class Window;
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
		sanguis::client::config::settings::object &,
		sanguis::client::gui::object &,
		sanguis::client::gui::menu::callbacks::object const &
	);

	~object();

	void
	process(
		sanguis::duration const &
	);

	void
	draw(
		sge::renderer::context::ffp &
	);

	void
	connection_error(
		fcppt::string const &message
	);
private:
	sanguis::client::config::settings::object &settings_;

	sanguis::client::gui::object &gui_;

	sanguis::client::gui::menu::callbacks::object const callbacks_;

	sge::cegui::toolbox::scoped_layout const scoped_layout_;

	sge::cegui::toolbox::scoped_gui_sheet const scoped_gui_sheet_;

	CEGUI::Window
		&connect_button_,
		&hostname_edit_,
		&port_edit_;

	CEGUI::Event::ScopedConnection const
		quickstart_connection_,
		quit_connection_,
		connect_connection_,
		hostname_change_connection_,
		port_change_connection_;

	typedef fcppt::scoped_ptr<
		sanguis::client::gui::menu::connection_box
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

	bool
	handle_text_changed(
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
