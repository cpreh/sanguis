#include <sanguis/client/load/resource/make_missing_texture.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/rect.hpp>
#include <sge/image2d/vector.hpp>
#include <sge/image2d/algorithm/fill.hpp>
#include <sge/image2d/store/rgba8.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/image2d/view/sub.hpp>
#include <sge/image2d/view/to_const.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/texture/create_planar_from_view.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/texture/const_part_unique_ptr.hpp>
#include <sge/texture/part_raw_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/fill.hpp>


sge::texture::const_part_unique_ptr
sanguis::client::load::resource::make_missing_texture(
	sge::renderer::device::core &_renderer
)
{
	sge::image2d::dim const dim{
		fcppt::math::dim::fill<
			sge::image2d::dim
		>(
			64u
		)
	};

	sge::image2d::store::rgba8 store{
		dim
	};

	sge::image2d::dim const half_dim{
		dim
		/
		2
	};

	sge::image::color::any::object const color1{
		sge::image::color::predef::magenta()
	};

	sge::image::color::any::object const color2{
		sge::image::color::predef::black()
	};

	sge::image2d::algorithm::fill(
		sge::image2d::view::sub(
			sge::image2d::view::object(
				store.wrapped_view()
			),
			sge::image2d::rect{
				sge::image2d::vector::null(),
				half_dim
			}
		),
		color1
	);

	sge::image2d::algorithm::fill(
		sge::image2d::view::sub(
			sge::image2d::view::object(
				store.wrapped_view()
			),
			sge::image2d::rect{
				sge::image2d::vector{
					0,
					half_dim.h()
				},
				half_dim
			}
		),
		color2
	);

	sge::image2d::algorithm::fill(
		sge::image2d::view::sub(
			sge::image2d::view::object(
				store.wrapped_view()
			),
			sge::image2d::rect{
				sge::image2d::vector{
					half_dim.w(),
					0
				},
				half_dim
			}
		),
		color2
	);

	sge::image2d::algorithm::fill(
		sge::image2d::view::sub(
			sge::image2d::view::object(
				store.wrapped_view()
			),
			sge::image2d::rect{
				sge::image2d::vector{
					half_dim.w(),
					half_dim.h()
				},
				half_dim
			}
		),
		color1
	);

	return
		fcppt::make_unique_ptr<
			sge::texture::part_raw_ptr
		>(
			sge::renderer::texture::create_planar_from_view(
				_renderer,
				sge::image2d::view::to_const(
					sge::image2d::view::object(
						store.wrapped_view()
					)
				),
				sge::renderer::texture::mipmap::off(),
				sge::renderer::resource_flags_field::null(),
				sge::renderer::texture::emulate_srgb::no
			)
		);
}
