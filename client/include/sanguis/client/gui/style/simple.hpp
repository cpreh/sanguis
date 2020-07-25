#ifndef SANGUIS_CLIENT_GUI_STYLE_SIMPLE_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_STYLE_SIMPLE_HPP_INCLUDED

#include <sanguis/client/load/resource/textures_fwd.hpp>
#include <sge/gui/fill_color_fwd.hpp>
#include <sge/gui/fill_level_fwd.hpp>
#include <sge/gui/text_color_fwd.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/gui/style/base.hpp>
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
	public sge::gui::style::base
{
	FCPPT_NONCOPYABLE(
		simple
	);
public:
	explicit
	simple(
		sanguis::client::load::resource::textures const &
	);

	~simple()
	override;
private:
	sge::rucksack::dim
	button_spacing() const
	override;

	void
	draw_button(
		sge::gui::renderer::base &,
		sge::renderer::context::ffp &,
		sge::rucksack::rect const &
	) const
	override;

	void
	draw_bar(
		sge::gui::renderer::base &,
		sge::renderer::context::ffp &,
		sge::rucksack::rect const &,
		sge::rucksack::axis,
		sge::gui::fill_level,
		sge::gui::fill_color const &
	) const
	override;

	sge::rucksack::padding
	frame_padding() const
	override;

	void
	draw_frame(
		sge::gui::renderer::base &,
		sge::renderer::context::ffp &,
		sge::rucksack::rect const &,
		sge::rucksack::padding
	) const
	override;

	sge::rucksack::dim
	edit_spacing() const
	override;

	void
	draw_edit(
		sge::gui::renderer::base &,
		sge::renderer::context::ffp &,
		sge::rucksack::rect const &
	) const
	override;

	sge::rucksack::dim
	image_spacing() const
	override;

	void
	draw_image(
		sge::gui::renderer::base &,
		sge::renderer::context::ffp &,
		sge::rucksack::rect const &
	) const
	override;

	sge::rucksack::dim
	text_spacing() const
	override;

	void
	draw_text(
		sge::gui::renderer::base &,
		sge::renderer::context::ffp &,
		sge::rucksack::rect const &
	) const
	override;

	void
	draw_transparent_frame(
		sge::gui::renderer::base &,
		sge::renderer::context::ffp &,
		sge::rucksack::rect const &
	) const;

	sge::gui::text_color
	text_color() const
	override;

	sge::rucksack::dim
	spacing() const;

	sanguis::client::load::resource::textures const &textures_;
};

}
}
}
}

#endif
