#ifndef SANGUIS_GUI_AUX__RENDERER_STATELESS_HPP_INCLUDED
#define SANGUIS_GUI_AUX__RENDERER_STATELESS_HPP_INCLUDED

#include <sanguis/gui/renderer/base.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text_parameters_fwd.hpp>
#include <sge/font/vector_fwd.hpp>
#include <sge/font/draw/static_text_fwd.hpp>
#include <sge/image/color/any/object_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/rect_fwd.hpp>
#include <sge/rucksack/vector_fwd.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace gui
{
namespace aux_
{
namespace renderer
{

class stateless
:
	public sanguis::gui::renderer::base
{
	FCPPT_NONCOPYABLE(
		stateless
	);
public:
	explicit
	stateless(
		sge::renderer::device::ffp &
	);

	~stateless()
	override;
private:
	void
	fill_rect(
		sge::renderer::context::ffp &,
		sge::rucksack::rect,
		sge::image::color::any::object const &
	)
	override;

	void
	draw_image(
		sge::renderer::context::ffp &,
		sge::texture::part const &,
		sge::rucksack::vector
	)
	override;

	void
	draw_image_repeat(
		sge::renderer::context::ffp &,
		sge::texture::part const &,
		sge::rucksack::rect
	)
	override;

	void
	draw_static_text(
		sge::renderer::context::ffp &,
		sge::font::draw::static_text const &
	)
	override;

	sge::renderer::device::ffp &renderer_;
};

}
}
}
}

#endif
