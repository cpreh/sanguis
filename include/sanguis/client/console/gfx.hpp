#ifndef SANGUIS_CLIENT_CONSOLE_GFX_HPP_INCLUDED
#define SANGUIS_CLIENT_CONSOLE_GFX_HPP_INCLUDED

#include <sge/console/gfx.hpp>
#include <sge/console/object_fwd.hpp>
#include <sge/console/output_line_limit.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/texture/planar_scoped_ptr.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace client
{
namespace console
{

class gfx
{
	FCPPT_NONCOPYABLE(
		gfx
	);
public:
	gfx(
		sge::console::object &,
		sge::renderer::device::ffp &,
		sge::font::object &,
		sge::image2d::system &,
		sge::input::keyboard::device &,
		sge::viewport::manager &,
		sge::console::output_line_limit
	);

	~gfx();

	sge::console::gfx &
	get();
private:
	void
	on_resize();

	sge::renderer::device::ffp &renderer_;

	sge::renderer::texture::planar_scoped_ptr const texture_;

	sge::console::gfx impl_;

	fcppt::signal::scoped_connection const resize_connection_;
};

}
}
}

#endif
