#ifndef SANGUIS_CREATOR_AUX_DESERIALIZATION_TILE_GRID_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX_DESERIALIZATION_TILE_GRID_HPP_INCLUDED

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


namespace sanguis
{
namespace creator
{
namespace aux
{
namespace deserialization
{

template<
	typename Grid
>
Grid
tile_grid(
	sge::parse::json::object const &_object
)
{
	return
		Grid(
			sge::parse::json::convert::to_static_container<
				typename Grid::dim
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
					typename Grid::value_type
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
						typename Grid::value_type
					>,
					std::placeholders::_1,
					fcppt::enum_max_value<
						typename Grid::value_type
					>::value
				)
			)
		);
}

}
}
}
}

#endif
