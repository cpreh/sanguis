#ifndef SANGUIS_GUI_WIDGET_EDIT_HPP_INCLUDED
#define SANGUIS_GUI_WIDGET_EDIT_HPP_INCLUDED

#include <sanguis/gui/duration.hpp>
#include <sanguis/gui/focus_change_fwd.hpp>
#include <sanguis/gui/get_focus_fwd.hpp>
#include <sanguis/gui/symbol.hpp>
#include <sanguis/gui/text_callback.hpp>
#include <sanguis/gui/text_function.hpp>
#include <sanguis/gui/renderer/base_fwd.hpp>
#include <sanguis/gui/style/base_fwd.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sanguis/gui/widget/edit_fwd.hpp>
#include <sanguis/gui/widget/optional_focus_fwd.hpp>
#include <sanguis/gui/widget/optional_ref_fwd.hpp>
#include <sge/font/char_type.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/font/draw/static_text.hpp>
#include <sge/input/keyboard/key_code_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/dummy.hpp>
#include <sge/timer/basic_decl.hpp>
#include <sge/timer/clocks/delta_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>
#include <fcppt/signal/object_decl.hpp>


namespace sanguis
{
namespace gui
{
namespace widget
{

class edit
:
	public sanguis::gui::widget::base
{
	FCPPT_NONCOPYABLE(
		edit
	);
public:
	SANGUIS_GUI_SYMBOL
	edit(
		sanguis::gui::style::base const &,
		sge::renderer::device::ffp &,
		sge::font::object &,
		sge::font::string const &
	);

	SANGUIS_GUI_SYMBOL
	~edit()
	override;

	SANGUIS_GUI_SYMBOL
	sge::font::string const &
	text() const;

	SANGUIS_GUI_SYMBOL
	fcppt::signal::auto_connection
	text_change(
		sanguis::gui::text_callback const &
	);

	SANGUIS_GUI_SYMBOL
	sge::rucksack::widget::base &
	layout()
	override;
private:
	void
	on_update(
		sanguis::gui::duration
	)
	override;

	void
	on_draw(
		sanguis::gui::renderer::base &,
		sge::renderer::context::ffp &
	)
	override;

	sanguis::gui::get_focus const
	on_click(
		sge::rucksack::vector
	)
	override;

	void
	on_key(
		sge::input::keyboard::key_code
	)
	override;

	void
	on_char(
		sge::font::char_type
	)
	override;

	void
	on_focus_changed(
		sanguis::gui::focus_change
	)
	override;

	sanguis::gui::widget::optional_ref const
	on_tab(
		sanguis::gui::widget::optional_focus &
	)
	override;

	void
	text_changed();

	sge::font::draw::static_text
	make_static_text();

	sanguis::gui::style::base const &style_;

	sge::renderer::device::ffp &renderer_;

	sge::font::object &font_;

	sge::font::string text_;

	sge::font::string::size_type position_;

	sge::rucksack::widget::dummy layout_;

	sge::font::draw::static_text static_text_;

	typedef
	sge::timer::clocks::delta<
		sanguis::gui::duration
	>
	diff_clock;

	typedef
	sge::timer::basic<
		diff_clock
	>
	diff_timer;

	diff_clock clock_;

	diff_timer cursor_blink_timer_;

	bool has_focus_;

	bool show_cursor_;

	typedef
	fcppt::signal::object<
		sanguis::gui::text_function
	>
	text_signal;

	text_signal text_change_;
};

}
}
}

#endif
