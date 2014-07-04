#ifndef SANGUIS_GUI_AUX__DRAW_IMAGE_STRETCHED_HPP_INCLUDED
#define SANGUIS_GUI_AUX__DRAW_IMAGE_STRETCHED_HPP_INCLUDED

#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/rect_fwd.hpp>
#include <sge/texture/part_fwd.hpp>


namespace sanguis
{
namespace gui
{
namespace aux_
{

void
draw_image_stretched(
	sge::renderer::device::ffp &,
	sge::renderer::context::ffp &,
	sge::texture::part const &,
	sge::rucksack::rect
);

}
}
}

#endif
