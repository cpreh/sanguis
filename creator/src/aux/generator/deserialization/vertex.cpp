#include <sanguis/creator/aux/generator/deserialization/vertex.hpp>
#include <sanguis/creator/geometry/vector.hpp>
#include <sanguis/creator/geometry/vertex.hpp>
#include <sanguis/creator/geometry/texture_point.hpp>
#include <sge/parse/json/convert/to_static_container.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/text.hpp>


sanguis::creator::geometry::vertex const
sanguis::creator::aux::generator::deserialization::vertex(
	sge::parse::json::object const &_object
)
{
	return
		sanguis::creator::geometry::vertex(
			sge::parse::json::convert::to_static_container<
				sanguis::creator::geometry::vector
			>(
				sge::parse::json::find_member_exn<
					sge::parse::json::array
				>(
					_object.members,
					FCPPT_TEXT("pos")
				)
			),
			sge::parse::json::convert::to_static_container<
				sanguis::creator::geometry::texture_point
			>(
				sge::parse::json::find_member_exn<
					sge::parse::json::array
				>(
					_object.members,
					FCPPT_TEXT("texcoords")
				)
			)
		);
}
