#ifndef SANGUIS_GUI_WIDGET_BUTTON_HPP_INCLUDED
#define SANGUIS_GUI_WIDGET_BUTTON_HPP_INCLUDED

#include <sanguis/gui/click_callback.hpp>
#include <sanguis/gui/click_function.hpp>
#include <sanguis/gui/get_focus_fwd.hpp>
#include <sanguis/gui/symbol.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sanguis/gui/widget/button_fwd.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/font/draw/static_text.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/vector_fwd.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/dummy.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>
#include <fcppt/signal/object_decl.hpp>


namespace sanguis
{
namespace gui
{
namespace widget
{

class button
:
	public sanguis::gui::widget::base
{
	FCPPT_NONCOPYABLE(
		button
	);
public:
	SANGUIS_GUI_SYMBOL
	button(
		sge::renderer::device::ffp &,
		sge::font::object &,
		sge::font::string const &
	);

	SANGUIS_GUI_SYMBOL
	~button();

	SANGUIS_GUI_SYMBOL
	fcppt::signal::auto_connection
	click(
		sanguis::gui::click_callback const &
	);

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

	sge::font::draw::static_text static_text_;

	sge::rucksack::widget::dummy layout_;

	typedef
	fcppt::signal::object<
		sanguis::gui::click_function
	>
	click_signal;

	click_signal click_;
};

}
}
}

#endif
