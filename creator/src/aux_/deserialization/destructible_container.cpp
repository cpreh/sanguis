#include <sanguis/creator/destructible_container.hpp>
#include <sanguis/creator/aux_/deserialization/destructible.hpp>
#include <sanguis/creator/aux_/deserialization/destructible_container.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/value.hpp>
#include <fcppt/algorithm/map.hpp>


sanguis::creator::destructible_container
sanguis::creator::aux_::deserialization::destructible_container(
	sge::parse::json::array const &_array
)
{
	return
		fcppt::algorithm::map<
			sanguis::creator::destructible_container
		>(
			_array.elements,
			[](
				sge::parse::json::value const &_value
			)
			{
				return
					sanguis::creator::aux_::deserialization::destructible(
						sge::parse::json::get<
							sge::parse::json::object
						>(
							_value
						)
					);
			}
		);
}
