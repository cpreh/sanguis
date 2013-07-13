#include <sanguis/creator/opening.hpp>
#include <sanguis/creator/opening_container.hpp>
#include <sanguis/creator/aux/serialization/opening_container.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/element_vector.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/convert/from_container.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/map.hpp>


sge::parse::json::array
sanguis::creator::aux::serialization::opening_container(
	sanguis::creator::opening_container const &_openings
)
{
	return
		sge::parse::json::array(
			fcppt::algorithm::map<
				sge::parse::json::element_vector
			>(
				_openings,
				[](
					sanguis::creator::opening const &_opening
				)
				{
					return
						sge::parse::json::convert::from_container(
							_opening.get()
						);
				}
			)
		);
}
