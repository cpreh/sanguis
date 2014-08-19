#ifndef SANGUIS_CLIENT_GUI_STYLE_SIMPLE_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_STYLE_SIMPLE_HPP_INCLUDED

#include <sanguis/client/load/resource/textures.hpp>
#include <sanguis/gui/fill_color_fwd.hpp>
#include <sanguis/gui/fill_level_fwd.hpp>
#include <sanguis/gui/text_color_fwd.hpp>
#include <sanguis/gui/renderer/base_fwd.hpp>
#include <sanguis/gui/style/base.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/axis_fwd.hpp>
#include <sge/rucksack/dim_fwd.hpp>
#include <sge/rucksack/padding_fwd.hpp>
#include <sge/rucksack/rect_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace client
{
namespace gui
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
	simple(
		sanguis::client::load::resource::textures const &
	);

	~simple()
	override;
private:
	sge::rucksack::dim const
	button_spacing() const
	override;

	void
	draw_button(
		sanguis::gui::renderer::base &,
		sge::renderer::context::ffp &,
		sge::rucksack::rect
	) const
	override;

	void
	draw_bar(
		sanguis::gui::renderer::base &,
		sge::renderer::context::ffp &,
		sge::rucksack::rect,
		sge::rucksack::axis,
		sanguis::gui::fill_level,
		sanguis::gui::fill_color const &
	) const
	override;

	sge::rucksack::padding const
	frame_padding() const
	override;

	void
	draw_frame(
		sanguis::gui::renderer::base &,
		sge::renderer::context::ffp &,
		sge::rucksack::rect,
		sge::rucksack::padding
	) const
	override;

	sge::rucksack::dim const
	edit_spacing() const
	override;

	void
	draw_edit(
		sanguis::gui::renderer::base &,
		sge::renderer::context::ffp &,
		sge::rucksack::rect
	) const
	override;

	sge::rucksack::dim const
	image_spacing() const
	override;

	void
	draw_image(
		sanguis::gui::renderer::base &,
		sge::renderer::context::ffp &,
		sge::rucksack::rect
	) const
	override;

	sge::rucksack::dim const
	text_spacing() const
	override;

	void
	draw_text(
		sanguis::gui::renderer::base &,
		sge::renderer::context::ffp &,
		sge::rucksack::rect
	) const
	override;

	sanguis::gui::text_color
	text_color() const
	override;

	sge::rucksack::dim const
	spacing() const;

	sanguis::client::load::resource::textures
	const &textures_;
};

}
}
}
}

#endif
