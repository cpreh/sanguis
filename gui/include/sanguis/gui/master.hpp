#ifndef SANGUIS_GUI_MASTER_HPP_INCLUDED
#define SANGUIS_GUI_MASTER_HPP_INCLUDED

#include <sanguis/gui/symbol.hpp>
#include <sanguis/gui/context_fwd.hpp>
#include <sanguis/gui/master_fwd.hpp>
#include <sanguis/gui/widget/base_fwd.hpp>
#include <sge/input/cursor/button_event_fwd.hpp>
#include <sge/input/cursor/object_fwd.hpp>
#include <sge/input/keyboard/char_event_fwd.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/input/keyboard/key_code_fwd.hpp>
#include <sge/input/keyboard/key_event_fwd.hpp>
#include <sge/input/keyboard/key_repeat_event_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>


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
		sge::input::keyboard::device &,
		sge::input::cursor::object &,
		sanguis::gui::context &,
		sanguis::gui::widget::base &
	);

	SANGUIS_GUI_SYMBOL
	~master();

	SANGUIS_GUI_SYMBOL
	void
	draw(
		sge::renderer::context::ffp &
	);

	SANGUIS_GUI_SYMBOL
	void
	update();
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

	sge::input::cursor::object &cursor_;

	sanguis::gui::context &context_;

	sanguis::gui::widget::base &widget_;

	fcppt::signal::scoped_connection const
		key_connection_,
		key_repeat_connection_,
		char_connection_,
		button_connection_;
};

}
}

#endif
