#ifndef SANGUIS_CLIENT_CONSOLE_GFX_HPP_INCLUDED
#define SANGUIS_CLIENT_CONSOLE_GFX_HPP_INCLUDED

#include <sge/console/object_ref.hpp>
#include <sge/console/gfx/object.hpp>
#include <sge/console/gfx/output_line_limit_fwd.hpp>
#include <sge/font/object_ref.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/renderer/target/viewport_fwd.hpp>
#include <sge/viewport/manager_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/signal/auto_connection.hpp>


namespace sanguis::client::console
{

class gfx
{
	FCPPT_NONMOVABLE(
		gfx
	);
public:
	gfx(
		sge::console::object_ref,
		sge::renderer::device::ffp_ref,
		sge::font::object_ref,
		sge::viewport::manager_ref,
		sge::console::gfx::output_line_limit
	);

	~gfx();

	[[nodiscard]]
	sge::console::gfx::object &
	get();
private:
	void
	on_resize(
		sge::renderer::target::viewport const &
	);

	sge::console::gfx::object impl_;

	fcppt::signal::auto_connection const resize_connection_;
};

}

#endif
