#include "shape_container.hpp"
#include "shape.hpp"
#include <sanguis/creator/geometry/shape_container.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/element_vector.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/algorithm/map.hpp>

sge::parse::json::array const
sanguis::creator::generator::serialization::shape_container(
	geometry::shape_container const &_shapes
)
{
	return
		sge::parse::json::array(
			fcppt::algorithm::map<
				sge::parse::json::element_vector
			>(
				_shapes,
				&serialization::shape
			)
		);
}
