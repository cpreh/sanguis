#include <sanguis/media_path.hpp>
#include <sanguis/client/console/gfx.hpp>
#include <sge/console/object_fwd.hpp>
#include <sge/console/gfx/font_color.hpp>
#include <sge/console/gfx/sprite_object.hpp>
#include <sge/console/gfx/sprite_parameters.hpp>
#include <sge/console/gfx/object.hpp>
#include <sge/console/gfx/output_line_limit.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/target/viewport_size.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/renderer/texture/create_planar_from_path.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/texture/part_raw_ref.hpp>
#include <sge/viewport/manager.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace
{

sge::console::gfx::sprite_object::dim const
make_sprite_dim(
	sge::renderer::device::ffp &
);

}

sanguis::client::console::gfx::gfx(
	sge::console::object &_console,
	sge::renderer::device::ffp &_renderer,
	sge::font::object &_font_object,
	sge::image2d::system &_image_loader,
	sge::input::keyboard::device &_keyboard,
	sge::viewport::manager &_viewport_manager,
	sge::console::gfx::output_line_limit const _history_size
)
:
	renderer_(
		_renderer
	),
	texture_(
		// TODO: Use resources here
		sge::renderer::texture::create_planar_from_path(
			sanguis::media_path()
			/ FCPPT_TEXT("console_back.png"),
			renderer_,
			_image_loader,
			sge::renderer::texture::mipmap::off(),
			sge::renderer::resource_flags_field::null(),
			sge::renderer::texture::emulate_srgb::yes
		)
	),
	impl_(
		_console,
		renderer_,
		sge::console::gfx::font_color(
			sge::image::color::predef::white()
		),
		_font_object,
		_keyboard,
		sge::console::gfx::sprite_object(
			sge::console::gfx::sprite_parameters()
			.texture(
				fcppt::make_shared_ptr<
					sge::texture::part_raw_ref
				>(
					*texture_
				)
			)
			.pos(
				sge::console::gfx::sprite_object::vector::null()
			)
			.size(
				::make_sprite_dim(
					renderer_
				)
			)
		),
		_history_size
	),
	resize_connection_(
		_viewport_manager.manage_callback(
			std::bind(
				&sanguis::client::console::gfx::on_resize,
				this
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
	return impl_;
}

void
sanguis::client::console::gfx::on_resize()
{
	impl_.background_sprite().size(
		::make_sprite_dim(
			renderer_
		)
	);
}

namespace
{

sge::console::gfx::sprite_object::dim const
make_sprite_dim(
	sge::renderer::device::ffp &_device
)
{
	sge::renderer::screen_size const viewport_dim(
		sge::renderer::target::viewport_size(
			_device.onscreen_target()
		)
	);

	return
		sge::console::gfx::sprite_object::dim(
			fcppt::cast::size<
				sge::console::gfx::sprite_object::dim::value_type
			>(
				fcppt::cast::to_signed(
					viewport_dim.w()
				)
			),
			fcppt::cast::size<
				sge::console::gfx::sprite_object::dim::value_type
			>(
				fcppt::cast::to_signed(
					viewport_dim.h()
					/
					fcppt::literal<
						sge::renderer::screen_unit
					>(
						2
					)
				)
			)
		);
}

}
