#include <sanguis/client/console/gfx.hpp>
#include <sanguis/client/load/resource/textures_fwd.hpp>
#include <sge/console/object_fwd.hpp>
#include <sge/console/gfx/font_color.hpp>
#include <sge/console/gfx/object.hpp>
#include <sge/console/gfx/output_line_limit.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/rect.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/input/focus/object_fwd.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/pixel_unit.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/viewport/manage_callback.hpp>
#include <sge/viewport/manager.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace
{

sge::font::rect const
make_console_rect(
	sge::renderer::target::viewport const &_viewport
);

}

sanguis::client::console::gfx::gfx(
	sge::console::object &_console,
	sge::renderer::device::ffp &_renderer,
	sge::font::object &_font_object,
	sge::input::focus::object &_focus,
	sge::viewport::manager &_viewport_manager,
	sge::console::gfx::output_line_limit const _history_size,
	sanguis::client::load::resource::textures const &_textures
)
:
	// TODO: Add a background again
	impl_(
		_console,
		_renderer,
		sge::console::gfx::font_color(
			sge::image::color::predef::white()
		),
		_font_object,
		_focus,
		::make_console_rect(
			_renderer.onscreen_target().viewport()
		),
		_history_size
	),
	resize_connection_(
		_viewport_manager.manage_callback(
			sge::viewport::manage_callback{
				std::bind(
					&sanguis::client::console::gfx::on_resize,
					this,
					std::placeholders::_1
				)
			}
		)
	)
{
}

sanguis::client::console::gfx::~gfx()
{
}

sge::console::gfx::object &
sanguis::client::console::gfx::get()
{
	return
		impl_;
}

void
sanguis::client::console::gfx::on_resize(
	sge::renderer::target::viewport const &_viewport
)
{
	impl_.area(
		::make_console_rect(
			_viewport
		)
	);
}

namespace
{

sge::font::rect const
make_console_rect(
	sge::renderer::target::viewport const &_viewport
)
{
	sge::renderer::pixel_rect::dim const viewport_dim(
		_viewport.get().size()
	);

	return
		sge::font::rect{
			fcppt::math::vector::null<
				sge::font::rect::vector
			>(),
			sge::font::rect::dim{
				fcppt::cast::size<
					sge::font::rect::value_type
				>(
					viewport_dim.w()
				),
				fcppt::cast::size<
					sge::font::rect::value_type
				>(
					viewport_dim.h()
					/
					fcppt::literal<
						sge::renderer::pixel_unit
					>(
						2
					)
				)
			}
		};
}

}
