#include <sanguis/client/draw2d/scene/background_dim.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/target/viewport_size.hpp>


sge::renderer::screen_size const
sanguis::client::draw2d::scene::background_dim(
	sge::renderer::device::core &_device
)
{
	return
		sge::renderer::target::viewport_size(
			_device.onscreen_target()
		);
}
