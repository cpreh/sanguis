#ifndef SANGUIS_GUI_STYLE_BASE_HPP_INCLUDED
#define SANGUIS_GUI_STYLE_BASE_HPP_INCLUDED

#include <sanguis/gui/fill_color_fwd.hpp>
#include <sanguis/gui/fill_level_fwd.hpp>
#include <sanguis/gui/symbol.hpp>
#include <sanguis/gui/text_color_fwd.hpp>
#include <sanguis/gui/style/base_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/axis_fwd.hpp>
#include <sge/rucksack/dim_fwd.hpp>
#include <sge/rucksack/padding_fwd.hpp>
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
	void
	draw_bar(
		sge::renderer::device::ffp &,
		sge::renderer::context::ffp &,
		sge::rucksack::rect,
		sge::rucksack::axis,
		sanguis::gui::fill_level,
		sanguis::gui::fill_color const &
	) const = 0;

	virtual
	sge::rucksack::padding const
	frame_padding() const = 0;

	virtual
	void
	draw_frame(
		sge::renderer::device::ffp &,
		sge::renderer::context::ffp &,
		sge::rucksack::rect,
		sge::rucksack::padding
	) const = 0;

	virtual
	sge::rucksack::dim const
	edit_spacing() const = 0;

	virtual
	void
	draw_edit(
		sge::renderer::device::ffp &,
		sge::renderer::context::ffp &,
		sge::rucksack::rect
	) const = 0;

	virtual
	sge::rucksack::dim const
	image_spacing() const = 0;

	virtual
	void
	draw_image(
		sge::renderer::device::ffp &,
		sge::renderer::context::ffp &,
		sge::rucksack::rect
	) const = 0;

	virtual
	sge::rucksack::dim const
	text_spacing() const = 0;

	virtual
	void
	draw_text(
		sge::renderer::device::ffp &,
		sge::renderer::context::ffp &,
		sge::rucksack::rect
	) const = 0;

	virtual
	sanguis::gui::text_color
	text_color() const = 0;
};

}
}
}

#endif
