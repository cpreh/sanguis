#ifndef SANGUIS_GUI_MASTER_HPP_INCLUDED
#define SANGUIS_GUI_MASTER_HPP_INCLUDED

#include <sanguis/gui/duration.hpp>
#include <sanguis/gui/context_fwd.hpp>
#include <sanguis/gui/master_fwd.hpp>
#include <sanguis/gui/symbol.hpp>
#include <sanguis/gui/background/base_fwd.hpp>
#include <sanguis/gui/main_area/base_fwd.hpp>
#include <sanguis/gui/widget/base_fwd.hpp>
#include <sanguis/gui/widget/optional_focus_fwd.hpp>
#include <sanguis/gui/widget/optional_ref_fwd.hpp>
#include <sge/input/cursor/button_event_fwd.hpp>
#include <sge/input/cursor/object_fwd.hpp>
#include <sge/input/keyboard/char_event_fwd.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/input/keyboard/key_code_fwd.hpp>
#include <sge/input/keyboard/key_event_fwd.hpp>
#include <sge/input/keyboard/key_repeat_event_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/scoped_connection.hpp>


namespace sanguis
{
namespace gui
{

class master
{
	FCPPT_NONCOPYABLE(
		master
	);
public:
	SANGUIS_GUI_SYMBOL
	master(
		sge::renderer::device::ffp &,
		sge::input::keyboard::device &,
		sge::input::cursor::object &,
		sanguis::gui::context &,
		sanguis::gui::main_area::base &
	);

	SANGUIS_GUI_SYMBOL
	~master();

	SANGUIS_GUI_SYMBOL
	void
	draw(
		sge::renderer::context::ffp &,
		sanguis::gui::background::base &
	);

	SANGUIS_GUI_SYMBOL
	void
	update(
		sanguis::gui::duration
	);
private:
	void
	key_event(
		sge::input::keyboard::key_event const &
	);

	void
	key_repeat_event(
		sge::input::keyboard::key_repeat_event const &
	);

	void
	char_event(
		sge::input::keyboard::char_event const &
	);

	void
	button_event(
		sge::input::cursor::button_event const &
	);

	void
	handle_key(
		sge::input::keyboard::key_code
	);

	sanguis::gui::widget::optional_ref const
	try_focus(
		sanguis::gui::widget::optional_focus
	);

	sanguis::gui::widget::base &
	widget();

	sge::renderer::device::ffp &renderer_;

	sge::input::cursor::object &cursor_;

	sanguis::gui::context &context_;

	sanguis::gui::main_area::base &main_area_;

	fcppt::signal::scoped_connection const
		key_connection_,
		key_repeat_connection_,
		char_connection_,
		button_connection_;
};

}
}

#endif
