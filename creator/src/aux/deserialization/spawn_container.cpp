#include <sanguis/creator/spawn_container.hpp>
#include <sanguis/creator/aux/deserialization/spawn.hpp>
#include <sanguis/creator/aux/deserialization/spawn_container.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/value.hpp>
#include <fcppt/algorithm/map.hpp>


sanguis::creator::spawn_container
sanguis::creator::aux::deserialization::spawn_container(
	sge::parse::json::array const &_array
)
{
	return
		fcppt::algorithm::map<
			sanguis::creator::spawn_container
		>(
			_array.elements,
			[](
				sge::parse::json::value const &_value
			)
			{
				return
					sanguis::creator::aux::deserialization::spawn(
						sge::parse::json::get<
							sge::parse::json::object
						>(
							_value
						)
					);
			}
		);
}
