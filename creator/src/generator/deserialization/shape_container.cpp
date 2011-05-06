#include "shape_container.hpp"
#include "shape.hpp"
#include <sanguis/creator/geometry/shape_container.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/value.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/tr1/functional.hpp>

sanguis::creator::geometry::shape_container const
sanguis::creator::generator::deserialization::shape_container(
	sge::parse::json::array const &_array
)
{
	return
		fcppt::algorithm::map<
			geometry::shape_container
		>(
			_array.elements,
			std::tr1::bind(
				&deserialization::shape,
				std::tr1::bind(
					sge::parse::json::get<
						sge::parse::json::object,
						sge::parse::json::value const
					>,
					std::tr1::placeholders::_1
				)
			)
		);
}
