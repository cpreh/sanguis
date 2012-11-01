#include <sanguis/creator/aux/generator/serialization/polygon.hpp>
#include <sanguis/creator/aux/generator/serialization/vertex.hpp>
#include <sanguis/creator/geometry/polygon.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/element_vector.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/algorithm/map.hpp>


sge::parse::json::array const
sanguis::creator::aux::generator::serialization::polygon(
	sanguis::creator::geometry::polygon const &_polygon
)
{
	return
		sge::parse::json::array(
			fcppt::algorithm::map<
				sge::parse::json::element_vector
			>(
				_polygon,
				sanguis::creator::aux::generator::serialization::vertex
			)
		);
}
