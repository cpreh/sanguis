#include <sanguis/creator/aux/generator/serialization/shape_container.hpp>
#include <sanguis/creator/aux/generator/serialization/shape.hpp>
#include <sanguis/creator/geometry/shape_container.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/element_vector.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/algorithm/map.hpp>


sge::parse::json::array const
sanguis::creator::aux::generator::serialization::shape_container(
	sanguis::creator::geometry::shape_container const &_shapes
)
{
	return
		sge::parse::json::array(
			fcppt::algorithm::map<
				sge::parse::json::element_vector
			>(
				_shapes,
				&sanguis::creator::aux::generator::serialization::shape
			)
		);
}
