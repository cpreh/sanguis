#include <sanguis/client/console/gfx.hpp>
#include <sanguis/media_path.hpp>
#include <sge/console/sprite_object.hpp>
#include <sge/console/sprite_parameters.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/image/colors.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/target/viewport_size.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/renderer/texture/create_planar_from_path.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/parameters_impl.hpp>
#include <sge/texture/part_raw_ref.hpp>
#include <sge/viewport/manager.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/signal/auto_connection.hpp>

namespace
{

sge::console::sprite_object::dim const
make_sprite_dim(
	sge::renderer::device &
);

}

sanguis::client::console::gfx::gfx(
	sge::console::object &_console,
	sge::renderer::device &_renderer,
	sge::font::object &_font_object,
	sge::image2d::system &_image_loader,
	sge::input::keyboard::device &_keyboard,
	sge::viewport::manager &_viewport_manager,
	sge::console::output_line_limit const _history_size
)
:
	renderer_(
		_renderer
	),
	texture_(
		sge::renderer::texture::create_planar_from_path(
			sanguis::media_path()
			/ FCPPT_TEXT("console_back.png"),
			renderer_,
			_image_loader,
			sge::renderer::texture::mipmap::off(),
			sge::renderer::resource_flags_field::null()
		)
	),
	impl_(
		_console,
		renderer_,
		sge::image::colors::white(),
		_font_object,
		_keyboard,
		sge::console::sprite_object(
			sge::console::sprite_parameters()
			.texture(
				fcppt::make_shared_ptr<
					sge::texture::part_raw_ref
				>(
					fcppt::ref(
						*texture_
					)
				)
			)
			.pos(
				sge::console::sprite_object::vector::null()
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
			std::tr1::bind(
				&client::console::gfx::on_resize,
				this
			)
		)
	)
{
}

sanguis::client::console::gfx::~gfx()
{
}

sge::console::gfx &
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

sge::console::sprite_object::dim const
make_sprite_dim(
	sge::renderer::device &_device
)
{
	sge::renderer::screen_size const viewport_dim(
		sge::renderer::target::viewport_size(
			_device.onscreen_target()
		)
	);

	return
		sge::console::sprite_object::dim(
			static_cast<
				sge::console::sprite_object::dim::value_type
			>(
				viewport_dim.w()
			),
			static_cast<
				sge::console::sprite_object::dim::value_type
			>(
				viewport_dim.h()
				/
				2
			)
		);
}

}
