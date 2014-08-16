#ifndef SANGUIS_GUI_RENDERER_BASE_HPP_INCLUDED
#define SANGUIS_GUI_RENDERER_BASE_HPP_INCLUDED

#include <sanguis/gui/symbol.hpp>
#include <sanguis/gui/renderer/base_fwd.hpp>
#include <sge/font/draw/static_text_fwd.hpp>
#include <sge/image/color/any/object_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/rect_fwd.hpp>
#include <sge/rucksack/vector_fwd.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace gui
{
namespace renderer
{

class base
{
	FCPPT_NONCOPYABLE(
		base
	);
protected:
	SANGUIS_GUI_SYMBOL
	base();
public:
	SANGUIS_GUI_SYMBOL
	virtual
	~base() = 0;

	virtual
	void
	fill_rect(
		sge::renderer::context::ffp &,
		sge::rucksack::rect,
		sge::image::color::any::object const &
	) = 0;

	virtual
	void
	draw_image(
		sge::renderer::context::ffp &,
		sge::texture::part const &,
		sge::rucksack::vector
	) = 0;

	virtual
	void
	draw_static_text(
		sge::renderer::context::ffp &,
		sge::font::draw::static_text const &
	) = 0;
};

}
}
}

#endif
