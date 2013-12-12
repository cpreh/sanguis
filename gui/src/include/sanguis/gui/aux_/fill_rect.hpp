#ifndef SANGUIS_GUI_AUX__FILL_RECT_HPP_INCLUDED
#define SANGUIS_GUI_AUX__FILL_RECT_HPP_INCLUDED

#include <sge/image/color/any/object_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/rect_fwd.hpp>


namespace sanguis
{
namespace gui
{
namespace aux_
{

void
fill_rect(
	sge::renderer::device::ffp &,
	sge::renderer::context::ffp &,
	sge::rucksack::rect const &,
	sge::image::color::any::object const &
);

}
}
}

#endif
