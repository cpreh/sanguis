#include <sanguis/creator/opening.hpp>
#include <sanguis/creator/opening_container.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/aux/deserialization/opening_container.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/value.hpp>
#include <sge/parse/json/convert/to_static_container.hpp>
#include <fcppt/algorithm/map.hpp>


sanguis::creator::opening_container
sanguis::creator::aux::deserialization::opening_container(
	sge::parse::json::array const &_array
)
{
	return
		fcppt::algorithm::map<
			sanguis::creator::opening_container
		>(
			_array.elements,
			[](
				sge::parse::json::value const &_value
			)
			{
				return
					sanguis::creator::opening(
						sge::parse::json::convert::to_static_container<
							sanguis::creator::pos
						>(
							sge::parse::json::get<
								sge::parse::json::array
							>(
								_value
							)
						)
					);
			}
		);
}
