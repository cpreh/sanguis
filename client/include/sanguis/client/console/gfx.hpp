#ifndef SANGUIS_CLIENT_CONSOLE_GFX_HPP_INCLUDED
#define SANGUIS_CLIENT_CONSOLE_GFX_HPP_INCLUDED

#include <sanguis/client/load/resource/textures_fwd.hpp>
#include <sge/console/object_fwd.hpp>
#include <sge/console/gfx/object.hpp>
#include <sge/console/gfx/output_line_limit_fwd.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/input/focus/object_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/target/viewport_fwd.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/scoped_connection.hpp>


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
		sge::input::focus::object &,
		sge::viewport::manager &,
		sge::console::gfx::output_line_limit,
		sanguis::client::load::resource::textures const &
	);

	~gfx();

	sge::console::gfx::object &
	get();
private:
	void
	on_resize(
		sge::renderer::target::viewport const &
	);

	sge::console::gfx::object impl_;

	fcppt::signal::scoped_connection const resize_connection_;
};

}
}
}

#endif
