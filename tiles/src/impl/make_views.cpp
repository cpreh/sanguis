#include <sanguis/model/animation_index.hpp>
#include <sanguis/model/cell_area_from_index.hpp>
#include <sanguis/model/cell_size.hpp>
#include <sanguis/model/dim.hpp>
#include <sanguis/model/image_size.hpp>
#include <sanguis/tiles/view_container.hpp>
#include <sanguis/tiles/impl/make_views.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/size.hpp>
#include <sge/image2d/view/sub.hpp>
#include <sge/parse/json/get_exn.hpp>
#include <sge/parse/json/int_type.hpp>
#include <sge/parse/json/value_fwd.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/math/box/structure_cast.hpp>
#include <fcppt/math/dim/fill.hpp>


sanguis::tiles::view_container
sanguis::tiles::impl::make_views(
	sge::image2d::view::const_object const &_view,
	sge::parse::json::value const &_value
)
{
	return
		fcppt::algorithm::map<
			sanguis::tiles::view_container
		>(
			sge::parse::json::get_exn<
				sge::parse::json::array const
			>(
				_value
			).elements,
			[
				&_view
			](
				sge::parse::json::value const &_element
			)
			{
				return
					sge::image2d::view::sub(
						_view,
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
										sge::image2d::view::size(
											_view
										)
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
						)
					);
			}
		);
}
