#include <sanguis/client/console/gfx.hpp>
#include <sanguis/media_path.hpp>
#include <sge/console/sprite_object.hpp>
#include <sge/console/sprite_parameters.hpp>
#include <sge/image/colors.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/renderer/texture/address_mode2.hpp>
#include <sge/renderer/texture/address_mode.hpp>
#include <sge/renderer/texture/create_planar_from_path.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/onscreen_target.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/parameters_impl.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/viewport/manager.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_shared_ptr.hpp>

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
	sge::font::metrics &_font_metrics,
	sge::image2d::system &_image_loader,
	sge::input::keyboard::device &_keyboard,
	sge::viewport::manager &_viewport_manager,
	sge::console::output_line_limit const _history_size
)
:
	renderer_(_renderer),
	impl_(
		_console,
		renderer_,
		sge::image::colors::white(),
		_font_metrics,
		_keyboard,
		sge::console::sprite_object(
			sge::console::sprite_parameters()
			.texture(
				fcppt::make_shared_ptr<
					sge::texture::part_raw
				>(
					sge::renderer::texture::create_planar_from_path(
						sanguis::media_path()
						/ FCPPT_TEXT("console_back.png"),
						renderer_,
						_image_loader,
						sge::renderer::texture::mipmap::off(),
						sge::renderer::texture::address_mode2(
							sge::renderer::texture::address_mode::clamp
						),
						sge::renderer::resource_flags::none
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
			.elements()
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
	sge::renderer::pixel_rect::dim const viewport_dim(
		_device.onscreen_target().viewport().get().size()
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
