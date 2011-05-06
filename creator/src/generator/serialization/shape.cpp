#include "shape.hpp"
#include "polygon.hpp"
#include <sanguis/creator/geometry/shape.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/int_type.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/string.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/text.hpp>

sge::parse::json::object const
sanguis::creator::generator::serialization::shape(
	geometry::shape const &_shape
)
{
	return
		sge::parse::json::object(
			fcppt::assign::make_container<
				sge::parse::json::member_vector
			>(
				sge::parse::json::member(
					FCPPT_TEXT("polygon"),
					serialization::polygon(
						_shape.polygon()
					)
				)
			)
			(
				sge::parse::json::member(
					FCPPT_TEXT("solidity"),
					static_cast<
						sge::parse::json::int_type
					>(
						_shape.solidity()
					)
				)
			)
			(
				sge::parse::json::member(
					FCPPT_TEXT("depth"),
					static_cast<
						sge::parse::json::int_type
					>(
						_shape.depth().get()
					)
				)
			)
			(
				sge::parse::json::member(
					FCPPT_TEXT("texture_name"),
					sge::parse::json::string(
						_shape.texture_name()
					)
				)
			)
			.container()
		);
}
