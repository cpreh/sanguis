#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_DRAW_NAME_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_DRAW_NAME_HPP_INCLUDED

#include <sge/font/object_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sanguis/client/draw2d/scene/shown_name_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace scene
{

void
draw_name(
	sge::renderer::device::ffp &,
	sge::font::object &,
	sge::renderer::context::ffp &,
	sanguis::client::draw2d::scene::shown_name const &
);

}
}
}
}

#endif
