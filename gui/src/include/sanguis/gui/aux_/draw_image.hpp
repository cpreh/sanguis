#ifndef SANGUIS_GUI_AUX__FILL_RECT_HPP_INCLUDED
#define SANGUIS_GUI_AUX__FILL_RECT_HPP_INCLUDED

#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/vector_fwd.hpp>
#include <sge/texture/part_fwd.hpp>


namespace sanguis
{
namespace gui
{
namespace aux_
{

void
draw_image(
	sge::renderer::device::ffp &,
	sge::renderer::context::ffp &,
	sge::texture::part const &,
	sge::rucksack::vector
);

}
}
}

#endif
