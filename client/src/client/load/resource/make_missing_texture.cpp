#include <sanguis/client/load/resource/make_missing_texture.hpp>
#include <sanguis/client/load/resource/texture_from_view.hpp>
#include <sge/image/size_type.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image/view/wrap.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/rect.hpp>
#include <sge/image2d/vector.hpp>
#include <sge/image2d/algorithm/fill.hpp>
#include <sge/image2d/store/rgba8.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/image2d/view/sub.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/texture/const_part_unique_ptr.hpp>
#include <sge/texture/part.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/fill.hpp>


sge::texture::const_part_unique_ptr
sanguis::client::load::resource::make_missing_texture(
	sge::renderer::device::core &_renderer,
	sge::image::size_type const _size,
	sge::image::color::any::object const &_color1,
	sge::image::color::any::object const &_color2
)
{
	sge::image2d::dim const dim{
		fcppt::math::dim::fill<
			sge::image2d::dim
		>(
			_size
		)
	};

	sge::image2d::store::rgba8 const store{
		dim,
		[
			dim,
			&_color1,
			&_color2
		](
			sge::image2d::store::rgba8::view_type const &_view
		)
		{
			sge::image2d::dim const half_dim{
				dim
				/
				fcppt::literal<
					sge::image::size_type
				>(
					2
				)
			};

			sge::image2d::algorithm::fill(
				sge::image2d::view::sub(
					sge::image2d::view::object(
						sge::image::view::wrap(
							_view
						)
					),
					sge::image2d::rect{
						sge::image2d::vector::null(),
						half_dim
					}
				),
				_color1,
				sge::image::algorithm::uninitialized::yes
			);

			sge::image2d::algorithm::fill(
				sge::image2d::view::sub(
					sge::image2d::view::object(
						sge::image::view::wrap(
							_view
						)
					),
					sge::image2d::rect{
						sge::image2d::vector{
							0,
							half_dim.h()
						},
						half_dim
					}
				),
				_color2,
				sge::image::algorithm::uninitialized::yes
			);

			sge::image2d::algorithm::fill(
				sge::image2d::view::sub(
					sge::image2d::view::object(
						sge::image::view::wrap(
							_view
						)
					),
					sge::image2d::rect{
						sge::image2d::vector{
							half_dim.w(),
							0
						},
						half_dim
					}
				),
				_color2,
				sge::image::algorithm::uninitialized::yes
			);

			sge::image2d::algorithm::fill(
				sge::image2d::view::sub(
					sge::image2d::view::object(
						sge::image::view::wrap(
							_view
						)
					),
					sge::image2d::rect{
						sge::image2d::vector{
							half_dim.w(),
							half_dim.h()
						},
						half_dim
					}
				),
				_color1,
				sge::image::algorithm::uninitialized::yes
			);
		}
	};

	return
		sanguis::client::load::resource::texture_from_view(
			_renderer,
			sge::image2d::view::const_object(
				store.const_wrapped_view()
			)
		);
}
