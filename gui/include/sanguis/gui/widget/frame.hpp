#ifndef SANGUIS_GUI_WIDGET_FRAME_HPP_INCLUDED
#define SANGUIS_GUI_WIDGET_FRAME_HPP_INCLUDED

#include <sanguis/gui/focus_change_fwd.hpp>
#include <sanguis/gui/get_focus_fwd.hpp>
#include <sanguis/gui/symbol.hpp>
#include <sanguis/gui/style/base_fwd.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sanguis/gui/widget/frame_fwd.hpp>
#include <sanguis/gui/widget/optional_focus_fwd.hpp>
#include <sanguis/gui/widget/optional_ref_fwd.hpp>
#include <sge/font/char_type.hpp>
#include <sge/input/keyboard/key_code_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/vector_fwd.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/frame.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace gui
{
namespace widget
{

class frame
:
	public sanguis::gui::widget::base
{
	FCPPT_NONCOPYABLE(
		frame
	);
public:
	SANGUIS_GUI_SYMBOL
	frame(
		sanguis::gui::style::base const &,
		sge::renderer::device::ffp &,
		sanguis::gui::widget::base &
	);

	SANGUIS_GUI_SYMBOL
	~frame()
	override;

	SANGUIS_GUI_SYMBOL
	sge::rucksack::widget::base &
	layout()
	override;
private:
	void
	on_draw(
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

	sanguis::gui::style::base const &style_;

	sge::renderer::device::ffp &renderer_;

	sanguis::gui::widget::base &child_;

	sge::rucksack::widget::frame layout_;
};

}
}
}

#endif
