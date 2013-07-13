#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/aux/deserialization/grid.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/value.hpp>
#include <sge/parse/json/convert/to_enum.hpp>
#include <sge/parse/json/convert/to_static_container.hpp>
#include <fcppt/enum_max_value.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <vector>
#include <fcppt/config/external_end.hpp>


sanguis::creator::grid
sanguis::creator::aux::deserialization::grid(
	sge::parse::json::object const &_object
)
{
	return
		sanguis::creator::grid(
			sge::parse::json::convert::to_static_container<
				sanguis::creator::grid::dim
			>(
				sge::parse::json::find_member_exn<
					sge::parse::json::array
				>(
					_object.members,
					FCPPT_TEXT("size")
				)
			),
			fcppt::algorithm::map<
				std::vector<
					sanguis::creator::tile
				>
			>(
				sge::parse::json::find_member_exn<
					sge::parse::json::array
				>(
					_object.members,
					FCPPT_TEXT("elements")
				).elements,
				std::bind(
					&sge::parse::json::convert::to_enum<
						sanguis::creator::tile
					>,
					std::placeholders::_1,
					fcppt::enum_max_value<
						sanguis::creator::tile
					>::value
				)
			)
		);
}
