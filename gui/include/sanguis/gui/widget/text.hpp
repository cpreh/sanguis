#ifndef SANGUIS_GUI_WIDGET_TEXT_HPP_INCLUDED
#define SANGUIS_GUI_WIDGET_TEXT_HPP_INCLUDED

#include <sanguis/gui/symbol.hpp>
#include <sanguis/gui/text_color.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sanguis/gui/widget/text_fwd.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/string.hpp>
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

class text
:
	public sanguis::gui::widget::base
{
	FCPPT_NONCOPYABLE(
		text
	);
public:
	SANGUIS_GUI_SYMBOL
	text(
		sge::renderer::device::ffp &,
		sge::font::object &,
		sge::font::string const &,
		sanguis::gui::text_color const &
	);

	SANGUIS_GUI_SYMBOL
	~text();

	SANGUIS_GUI_SYMBOL
	void
	value(
		sge::font::string const &
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

	sge::renderer::device::ffp &renderer_;

	sge::font::object &font_;

	sanguis::gui::text_color const text_color_;

	sge::font::string value_;

	sge::rucksack::widget::dummy layout_;
};

}
}
}

#endif

