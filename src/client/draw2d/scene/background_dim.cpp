#include <sanguis/client/draw2d/scene/background_dim.hpp>
#include <sge/renderer/viewport_size.hpp>
#include <fcppt/math/dim/structure_cast.hpp>

sge::renderer::screen_size const
sanguis::client::draw2d::scene::background_dim(
	sge::renderer::device &_device
)
{
	return
		sge::renderer::viewport_size(
			_device
		);
}
