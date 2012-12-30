#include <sanguis/creator/aux/generator/deserialization/shape_container.hpp>
#include <sanguis/creator/aux/generator/deserialization/shape.hpp>
#include <sanguis/creator/geometry/shape_container.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/value.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::creator::geometry::shape_container const
sanguis::creator::aux::generator::deserialization::shape_container(
	sge::parse::json::array const &_array
)
{
	return
		fcppt::algorithm::map<
			sanguis::creator::geometry::shape_container
		>(
			_array.elements,
			std::bind(
				&sanguis::creator::aux::generator::deserialization::shape,
				std::bind(
					sge::parse::json::get<
						sge::parse::json::object,
						sge::parse::json::value const
					>,
					std::placeholders::_1
				)
			)
		);
}
