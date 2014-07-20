#ifndef SANGUIS_GUI_AUX__STYLE_SIMPLE_HPP_INCLUDED
#define SANGUIS_GUI_AUX__STYLE_SIMPLE_HPP_INCLUDED

#include <sanguis/gui/style/base.hpp>
#include <sge/image/color/any/object_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/dim_fwd.hpp>
#include <sge/rucksack/rect_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace gui
{
namespace aux_
{
namespace style
{

class simple
:
	public sanguis::gui::style::base
{
	FCPPT_NONCOPYABLE(
		simple
	);
public:
	simple();

	~simple()
	override;
private:
	sge::rucksack::dim const
	button_spacing() const
	override;

	void
	draw_button(
		sge::renderer::device::ffp &,
		sge::renderer::context::ffp &,
		sge::rucksack::rect
	) const
	override;

	sge::image::color::any::object
	text_color() const
	override;

	sge::rucksack::dim const
	spacing() const;
};

}
}
}
}

#endif
