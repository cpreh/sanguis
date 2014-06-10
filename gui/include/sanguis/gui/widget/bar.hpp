#ifndef SANGUIS_GUI_WIDGET_BAR_HPP_INCLUDED
#define SANGUIS_GUI_WIDGET_BAR_HPP_INCLUDED

#include <sanguis/gui/symbol.hpp>
#include <sanguis/gui/widget/bar_fwd.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/dim_fwd.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/dummy.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sanguis
{
namespace gui
{
namespace widget
{

class bar
:
	public sanguis::gui::widget::base
{
	FCPPT_NONCOPYABLE(
		bar
	);
public:
	FCPPT_MAKE_STRONG_TYPEDEF(
		float,
		fill_level
	);

	SANGUIS_GUI_SYMBOL
	bar(
		sge::renderer::device::ffp &,
		sge::rucksack::dim,
		sge::image::color::any::object const &,
		sanguis::gui::widget::bar::fill_level
	);

	SANGUIS_GUI_SYMBOL
	~bar()
	override;

	SANGUIS_GUI_SYMBOL
	void
	value(
		sanguis::gui::widget::bar::fill_level
	);
private:
	void
	on_draw(
		sge::renderer::context::ffp &
	)
	override;

	sge::rucksack::widget::base &
	layout()
	override;

	sge::renderer::device::ffp &renderer_;

	sge::image::color::any::object const foreground_;

	sanguis::gui::widget::bar::fill_level value_;

	sge::rucksack::widget::dummy layout_;
};

}
}
}

#endif
