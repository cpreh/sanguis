#include <sanguis/client/load/tiles/make_textures.hpp>
#include <sanguis/client/load/tiles/texture_container.hpp>
#include <sanguis/tiles/area_container.hpp>
#include <sge/image2d/rect.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/texture/part.hpp>
#include <sge/texture/part_raw_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/box/contains.hpp>
#include <fcppt/math/box/structure_cast.hpp>


sanguis::client::load::tiles::texture_container
sanguis::client::load::tiles::make_textures(
	sge::texture::part const &_part,
	sanguis::tiles::area_container const &_areas
)
{
	return
		fcppt::algorithm::map<
			sanguis::client::load::tiles::texture_container
		>(
			_areas,
			[
				&_part
			](
				sge::image2d::rect const _rect
			)
			{
				sge::renderer::lock_rect const rect(
					fcppt::math::box::structure_cast<
						sge::renderer::lock_rect,
						fcppt::cast::size_fun
					>(
						_rect
					)
				);

				FCPPT_ASSERT_PRE(
					fcppt::math::box::contains(
						_part.area(),
						rect
					)
				);

				return
					fcppt::make_unique_ptr<
						sge::texture::part_raw_ref
					>(
						_part.texture(),
						rect
					);
			}
		);
}
