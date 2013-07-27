#include <sanguis/creator/spawn.hpp>
#include <sanguis/creator/spawn_container.hpp>
#include <sanguis/creator/aux/serialization/spawn.hpp>
#include <sanguis/creator/aux/serialization/spawn_container.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/element_vector.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/algorithm/map.hpp>


sge::parse::json::array
sanguis::creator::aux::serialization::spawn_container(
	sanguis::creator::spawn_container const &_spawns
)
{
	return
		sge::parse::json::array(
			fcppt::algorithm::map<
				sge::parse::json::element_vector
			>(
				_spawns,
				[](
					sanguis::creator::spawn const &_spawn
				)
				{
					return
						sanguis::creator::aux::serialization::spawn(
							_spawn
						);
				}
			)
		);
}
