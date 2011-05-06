#include "vertex.hpp"
#include <sanguis/creator/geometry/vertex.hpp>
#include <sge/parse/json/convert/from_container.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/member_vector.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/text.hpp>

sge::parse::json::object const
sanguis::creator::generator::serialization::vertex(
	geometry::vertex const &_vertex
)
{
	return
		sge::parse::json::object(
			fcppt::assign::make_container<
				sge::parse::json::member_vector
			>(
				sge::parse::json::member(
					FCPPT_TEXT("pos"),
					sge::parse::json::convert::from_container(
						_vertex.pos()
					)
				)
			)
			(
				sge::parse::json::member(
					FCPPT_TEXT("texcoords"),
					sge::parse::json::convert::from_container(
						_vertex.texcoords()
					)
				)
			)
			.container()
		);
}
