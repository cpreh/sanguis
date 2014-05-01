#include <sanguis/creator/destructible.hpp>
#include <sanguis/creator/destructible_container.hpp>
#include <sanguis/creator/aux_/serialization/destructible.hpp>
#include <sanguis/creator/aux_/serialization/destructible_container.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/element_vector.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/algorithm/map.hpp>


sge::parse::json::array
sanguis::creator::aux_::serialization::destructible_container(
	sanguis::creator::destructible_container const &_destructibles
)
{
	return
		sge::parse::json::array(
			fcppt::algorithm::map<
				sge::parse::json::element_vector
			>(
				_destructibles,
				[](
					sanguis::creator::destructible const &_destructible
				)
				{
					return
						sanguis::creator::aux_::serialization::destructible(
							_destructible
						);
				}
			)
		);
}
