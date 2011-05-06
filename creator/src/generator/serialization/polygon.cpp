#include "polygon.hpp"
#include "vertex.hpp"
#include <sanguis/creator/geometry/polygon.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/element_vector.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/algorithm/map.hpp>

sge::parse::json::array const
sanguis::creator::generator::serialization::polygon(
	geometry::polygon const &_polygon
)
{
	return
		sge::parse::json::array(
			fcppt::algorithm::map<
				sge::parse::json::element_vector
			>(
				_polygon,
				serialization::vertex	
			)
		);
}
