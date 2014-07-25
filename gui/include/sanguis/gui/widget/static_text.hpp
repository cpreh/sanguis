#ifndef SANGUIS_GUI_WIDGET_STATIC_TEXT_HPP_INCLUDED
#define SANGUIS_GUI_WIDGET_STATIC_TEXT_HPP_INCLUDED

#include <sanguis/gui/symbol.hpp>
#include <sanguis/gui/text_color.hpp>
#include <sanguis/gui/style/base_fwd.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sanguis/gui/widget/static_text_fwd.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/font/draw/static_text.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/dummy.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace gui
{
namespace widget
{

class static_text
:
	public sanguis::gui::widget::base
{
	FCPPT_NONCOPYABLE(
		static_text
	);
public:
	SANGUIS_GUI_SYMBOL
	static_text(
		sanguis::gui::style::base const &,
		sge::renderer::device::ffp &,
		sge::font::object &,
		sge::font::string const &,
		sanguis::gui::text_color const &
	);

	SANGUIS_GUI_SYMBOL
	~static_text()
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

	sanguis::gui::style::base const &style_;

	sge::renderer::device::ffp &renderer_;

	sge::font::draw::static_text static_text_;

	sge::rucksack::widget::dummy layout_;
};

}
}
}

#endif

