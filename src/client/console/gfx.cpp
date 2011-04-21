#include "gfx.hpp"
#include "../../media_path.hpp"
#include <sge/console/sprite_object.hpp>
#include <sge/console/sprite_parameters.hpp>
#include <sge/image/colors.hpp>
#include <sge/image2d/create_texture.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/texture/filter/linear.hpp>
#include <sge/renderer/texture/address_mode2.hpp>
#include <sge/renderer/texture/address_mode.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/parameters_impl.hpp>
#include <sge/texture/part_raw.hpp>
#include <sge/viewport/manager.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_shared_ptr.hpp>

sanguis::client::console::gfx::gfx(
	sge::console::object &_console,
	sge::renderer::device_ptr const _renderer,
	sge::font::metrics_ptr const _font_metrics,
	sge::image2d::multi_loader &_image_loader,
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
					sge::image2d::create_texture(
						sanguis::media_path()
						/ FCPPT_TEXT("console_back.png"),
						renderer_,
						_image_loader,
						sge::renderer::texture::filter::linear,
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
				sge::console::sprite_object::dim(
					static_cast<
						sge::console::sprite_object::unit
					>(
						1024 // FIXME!
					),
					static_cast<
						sge::console::sprite_object::unit
					>(
						768 / 2 // FIXME!
					)
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
}
