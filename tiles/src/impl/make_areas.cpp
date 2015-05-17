#include <sanguis/model/animation_index.hpp>
#include <sanguis/model/cell_area_from_index.hpp>
#include <sanguis/model/cell_size.hpp>
#include <sanguis/model/dim.hpp>
#include <sanguis/model/image_size.hpp>
#include <sanguis/tiles/area_container.hpp>
#include <sanguis/tiles/impl/make_areas.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/rect.hpp>
#include <sge/parse/json/get_exn.hpp>
#include <sge/parse/json/int_type.hpp>
#include <sge/parse/json/value_fwd.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/math/box/structure_cast.hpp>
#include <fcppt/math/dim/fill.hpp>


sanguis::tiles::area_container
sanguis::tiles::impl::make_areas(
	sge::image2d::dim const _size,
	sge::parse::json::value const &_value
)
{
	return
		fcppt::algorithm::map<
			sanguis::tiles::area_container
		>(
			sge::parse::json::get_exn<
				sge::parse::json::array const
			>(
				_value
			).elements,
			[
				_size
			](
				sge::parse::json::value const &_element
			)
			{
				return
					fcppt::math::box::structure_cast<
						sge::image2d::rect,
						fcppt::cast::size_fun
					>(
						// TODO: Put this function somewhere else
						sanguis::model::cell_area_from_index(
							sanguis::model::image_size(
								fcppt::math::dim::structure_cast<
									sanguis::model::dim,
									fcppt::cast::size_fun
								>(
									_size
								)
							),
							sanguis::model::cell_size(
								fcppt::math::dim::fill<
									sanguis::model::dim
								>(
									// TODO: Read this from the json file
									96ul
								)
							),
							fcppt::cast::size<
								sanguis::model::animation_index
							>(
								fcppt::cast::to_unsigned(
									sge::parse::json::get_exn<
										sge::parse::json::int_type
									>(
										_element
									)
								)
							)
						)
					);
			}
		);
}
