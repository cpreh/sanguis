#include "polygon.hpp"
#include "vertex.hpp"
#include <sanguis/creator/geometry/polygon.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/value.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/tr1/functional.hpp>

sanguis::creator::geometry::polygon const
sanguis::creator::generator::deserialization::polygon(
	sge::parse::json::array const &_array
)
{
	return
		fcppt::algorithm::map<
			geometry::polygon
		>(
			_array.elements,
			std::tr1::bind(
				&deserialization::vertex,
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
