#include <sanguis/client/load/tiles/make_textures.hpp>
#include <sanguis/client/load/tiles/texture_container.hpp>
#include <sanguis/model/animation_index.hpp>
#include <sanguis/model/cell_area_from_index.hpp>
#include <sanguis/model/cell_size.hpp>
#include <sanguis/model/dim.hpp>
#include <sanguis/model/image_size.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/int_type.hpp>
#include <sge/parse/json/value.hpp>
#include <sge/texture/part.hpp>
#include <sge/texture/part_raw_ref.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/dim/fill.hpp>


sanguis::client::load::tiles::texture_container
sanguis::client::load::tiles::make_textures(
	sge::texture::part const &_part,
	sge::parse::json::value const &_value
)
{
	return
		fcppt::algorithm::map<
			sanguis::client::load::tiles::texture_container
		>(
			sge::parse::json::get<
				sge::parse::json::array const
			>(
				_value
			).elements,
			[
				&_part
			](
				sge::parse::json::value const &_element
			)
			{
				return
					fcppt::make_shared_ptr<
						sge::texture::part_raw_ref
					>(
						_part.texture(),
						// TODO: Put this function somewhere else
						sanguis::model::cell_area_from_index(
							sanguis::model::image_size(
								fcppt::math::dim::structure_cast<
									sanguis::model::dim
								>(
									_part.size()
								)
							),
							sanguis::model::cell_size(
								fcppt::math::dim::fill<
									sanguis::model::dim::dim_wrapper::value
								>(
									// TODO: Read this from the json file
									96ul
								)
							),
							fcppt::cast::size<
								sanguis::model::animation_index
							>(
								fcppt::cast::to_unsigned(
									sge::parse::json::get<
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
