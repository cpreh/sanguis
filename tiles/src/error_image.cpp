#include <sanguis/creator/tile_size.hpp>
#include <sanguis/tiles/error.hpp>
#include <sanguis/tiles/error_image.hpp>
#include <sanguis/tiles/impl/error_image_color_pair.hpp>
#include <sanguis/tiles/impl/error_image_colors.hpp>
#include <sge/image/size_type.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/view/wrap.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/rect.hpp>
#include <sge/image2d/vector.hpp>
#include <sge/image2d/algorithm/fill.hpp>
#include <sge/image2d/store/object.hpp>
#include <sge/image2d/store/srgba8.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/image2d/view/sub.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/tuple/get.hpp>

sge::image2d::store::object sanguis::tiles::error_image(sanguis::tiles::error const _error)
{
  sanguis::tiles::impl::error_image_color_pair const colors(
      sanguis::tiles::impl::error_image_colors(_error));

  sge::image2d::dim const dim{
      fcppt::math::dim::fill<sge::image2d::dim>(sanguis::creator::tile_size::value)};

  using store_type = sge::image2d::store::srgba8;

  return sge::image2d::store::object{store_type{
      dim,
      store_type::init_function{
          [dim, &colors](store_type::view_type const &_view)
          {
            sge::image2d::dim const half_dim{
                (dim / fcppt::literal<sge::image::size_type>(2)).get_unsafe()};

            sge::image2d::algorithm::fill(
                sge::image2d::view::sub(
                    sge::image2d::view::object(sge::image::view::wrap(_view)),
                    sge::image2d::rect{
                        fcppt::math::vector::null<sge::image2d::vector>(), half_dim}),
                fcppt::tuple::get<0U>(colors),
                sge::image::algorithm::uninitialized::yes);

            sge::image2d::algorithm::fill(
                sge::image2d::view::sub(
                    sge::image2d::view::object(sge::image::view::wrap(_view)),
                    sge::image2d::rect{sge::image2d::vector{0U, half_dim.h()}, half_dim}),
                fcppt::tuple::get<1U>(colors),
                sge::image::algorithm::uninitialized::yes);

            sge::image2d::algorithm::fill(
                sge::image2d::view::sub(
                    sge::image2d::view::object(sge::image::view::wrap(_view)),
                    sge::image2d::rect{sge::image2d::vector{half_dim.w(), 0U}, half_dim}),
                fcppt::tuple::get<1U>(colors),
                sge::image::algorithm::uninitialized::yes);

            sge::image2d::algorithm::fill(
                sge::image2d::view::sub(
                    sge::image2d::view::object(sge::image::view::wrap(_view)),
                    sge::image2d::rect{sge::image2d::vector{half_dim.w(), half_dim.h()}, half_dim}),
                fcppt::tuple::get<0U>(colors),
                sge::image::algorithm::uninitialized::yes);
          }}}};
}
