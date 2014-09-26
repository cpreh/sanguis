#include <sanguis/client/console/gfx.hpp>
#include <sanguis/client/load/resource/texture_identifier.hpp>
#include <sanguis/client/load/resource/textures.hpp>
#include <sge/console/object_fwd.hpp>
#include <sge/console/gfx/font_color.hpp>
#include <sge/console/gfx/object.hpp>
#include <sge/console/gfx/output_line_limit.hpp>
#include <sge/console/gfx/sprite_object.hpp>
#include <sge/console/gfx/sprite_parameters.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/pixel_unit.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/texture/part_raw_ref.hpp>
#include <sge/viewport/manager.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace
{

sge::console::gfx::sprite_object::dim const
make_sprite_dim(
	sge::renderer::target::viewport const &_viewport
);

}

sanguis::client::console::gfx::gfx(
	sge::console::object &_console,
	sge::renderer::device::ffp &_renderer,
	sge::font::object &_font_object,
	sge::input::keyboard::device &_keyboard,
	sge::viewport::manager &_viewport_manager,
	sge::console::gfx::output_line_limit const _history_size,
	sanguis::client::load::resource::textures const &_textures
)
:
	impl_(
		_console,
		_renderer,
		sge::console::gfx::font_color(
			sge::image::color::predef::white()
		),
		_font_object,
		_keyboard,
		sge::console::gfx::sprite_object(
			sge::console::gfx::sprite_parameters()
			.texture(
				sge::console::gfx::sprite_object::texture_type{
					_textures.load(
						sanguis::client::load::resource::texture_identifier(
							FCPPT_TEXT("console_background")
						)
					)
				}
			)
			.pos(
				sge::console::gfx::sprite_object::vector::null()
			)
			.size(
				::make_sprite_dim(
					_renderer.onscreen_target().viewport()
				)
			)
		),
		_history_size
	),
	resize_connection_(
		_viewport_manager.manage_callback(
			std::bind(
				&sanguis::client::console::gfx::on_resize,
				this,
				std::placeholders::_1
			)
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
	impl_.background_sprite().size(
		::make_sprite_dim(
			_viewport
		)
	);
}

namespace
{

sge::console::gfx::sprite_object::dim const
make_sprite_dim(
	sge::renderer::target::viewport const &_viewport
)
{
	sge::renderer::pixel_rect::dim const viewport_dim(
		_viewport.get().size()
	);

	return
		sge::console::gfx::sprite_object::dim(
			fcppt::cast::size<
				sge::console::gfx::sprite_object::dim::value_type
			>(
				viewport_dim.w()
			),
			fcppt::cast::size<
				sge::console::gfx::sprite_object::dim::value_type
			>(
				viewport_dim.h()
				/
				fcppt::literal<
					sge::renderer::pixel_unit
				>(
					2
				)
			)
		);
}

}
