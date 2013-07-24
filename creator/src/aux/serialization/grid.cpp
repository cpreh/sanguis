#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/aux/serialization/grid.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/element_vector.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/convert/from_container.hpp>
#include <sge/parse/json/convert/from_enum.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/assign/make_container.hpp>


sge::parse::json::object
sanguis::creator::aux::serialization::grid(
	sanguis::creator::grid const &_grid
)
{
	return
		sge::parse::json::object(
			fcppt::assign::make_container<
				sge::parse::json::member_map
			>(
				sge::parse::json::member(
					FCPPT_TEXT("size"),
					sge::parse::json::convert::from_container(
						_grid.size()
					)
				)
			)(
				sge::parse::json::member(
					FCPPT_TEXT("elements"),
					sge::parse::json::array(
						fcppt::algorithm::map<
							sge::parse::json::element_vector
						>(
							_grid,
							&sge::parse::json::convert::from_enum<
								sanguis::creator::tile
							>
						)
					)
				)
			)
		);
}
