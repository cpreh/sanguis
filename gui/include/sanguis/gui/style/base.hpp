#ifndef SANGUIS_GUI_STYLE_BASE_HPP_INCLUDED
#define SANGUIS_GUI_STYLE_BASE_HPP_INCLUDED

#include <sanguis/gui/symbol.hpp>
#include <sanguis/gui/style/base_fwd.hpp>
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
namespace style
{

class base
{
	FCPPT_NONCOPYABLE(
		base
	);
protected:
	base();
public:
	SANGUIS_GUI_SYMBOL
	virtual
	~base() = 0;

	virtual
	sge::rucksack::dim const
	button_spacing() const = 0;

	virtual
	void
	draw_button(
		sge::renderer::device::ffp &,
		sge::renderer::context::ffp &,
		sge::rucksack::rect
	) const = 0;

	virtual
	sge::image::color::any::object
	text_color() const = 0;
};

}
}
}

#endif
