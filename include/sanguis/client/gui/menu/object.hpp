#ifndef SANGUIS_CLIENT_GUI_MENU_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_MENU_OBJECT_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/client/gui/menu/callbacks/object.hpp>
#include <sanguis/client/config/settings/object_fwd.hpp>
#include <sanguis/gui/context.hpp>
#include <sanguis/gui/master.hpp>
#include <sanguis/gui/widget/box_container.hpp>
#include <sanguis/gui/widget/button.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/input/cursor/object_fwd.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/scoped_connection.hpp>


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
		sge::renderer::device::ffp &,
		sge::viewport::manager &,
		sge::font::object &,
		sge::input::cursor::object &,
		sge::input::keyboard::device &,
		sanguis::client::config::settings::object &,
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

	/*
	void
	connection_error(
		fcppt::string const &message
	);*/
private:
	void
	handle_quickstart();

	sanguis::client::config::settings::object &settings_;

	sanguis::gui::context gui_context_;

	sanguis::client::gui::menu::callbacks::object const callbacks_;

	sanguis::gui::widget::button quickstart_button_;

	sanguis::gui::widget::button quit_button_;

	sanguis::gui::widget::box_container main_container_;

	sanguis::gui::master gui_master_;

	fcppt::signal::scoped_connection const
		quickstart_connection_,
		quit_connection_;

/*
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
	*/
};

}
}
}
}

#endif
