#include <sanguis/exception.hpp>
#include <sanguis/client/load/tiles/make_textures.hpp>
#include <sanguis/client/load/tiles/texture_container.hpp>
#include <sanguis/tiles/area_container.hpp>
#include <sge/image2d/rect.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/texture/part.hpp>
#include <sge/texture/part_raw_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/not.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/unique_ptr_to_const.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/box/contains.hpp>
#include <fcppt/math/box/structure_cast.hpp>

sanguis::client::load::tiles::texture_container sanguis::client::load::tiles::make_textures(
    sge::texture::part const &_part, sanguis::tiles::area_container const &_areas)
{
  return fcppt::algorithm::map<sanguis::client::load::tiles::texture_container>(
      _areas,
      [&_part](sge::image2d::rect const &_rect)
      {
        auto const rect(
            fcppt::math::box::structure_cast<sge::renderer::lock_rect, fcppt::cast::size_fun>(
                _rect));

        if (fcppt::not_(fcppt::math::box::contains(_part.area(), rect)))
        {
          throw sanguis::exception{FCPPT_TEXT("make_textures: area not inside rect")};
        }

        return fcppt::unique_ptr_to_const(fcppt::unique_ptr_to_base<sge::texture::part>(
            fcppt::make_unique_ptr<sge::texture::part_raw_ref>(_part.texture(), rect)));
      });
}
