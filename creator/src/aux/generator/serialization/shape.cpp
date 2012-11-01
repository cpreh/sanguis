#include <sanguis/creator/aux/generator/serialization/shape.hpp>
#include <sanguis/creator/aux/generator/serialization/polygon.hpp>
#include <sanguis/creator/geometry/shape.hpp>
#include <sge/parse/json/convert/from_enum.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/int_type.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/string.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/text.hpp>


sge::parse::json::object const
sanguis::creator::aux::generator::serialization::shape(
	sanguis::creator::geometry::shape const &_shape
)
{
	return
		sge::parse::json::object(
			fcppt::assign::make_container<
				sge::parse::json::member_map
			>(
				sge::parse::json::member(
					FCPPT_TEXT("polygon"),
					sanguis::creator::aux::generator::serialization::polygon(
						_shape.polygon()
					)
				)
			)
			(
				sge::parse::json::member(
					FCPPT_TEXT("solidity"),
					sge::parse::json::convert::from_enum(
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
