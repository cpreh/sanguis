#include "background_dim.hpp"
#include <sge/renderer/device.hpp>
#include <sge/renderer/onscreen_target.hpp>
#include <sge/renderer/viewport.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>

sge::renderer::screen_size const
sanguis::client::draw2d::scene::background_dim(
	sge::renderer::device_ptr const _device
)
{
	return
		fcppt::math::dim::structure_cast<
			sge::renderer::screen_size
		>(
			_device->onscreen_target()->viewport().get().size()
		);
}
