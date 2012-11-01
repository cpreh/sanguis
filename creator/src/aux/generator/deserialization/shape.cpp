#include <sanguis/creator/aux/generator/deserialization/shape.hpp>
#include <sanguis/creator/aux/generator/deserialization/polygon.hpp>
#include <sanguis/creator/geometry/depth.hpp>
#include <sanguis/creator/geometry/shape.hpp>
#include <sanguis/creator/geometry/solidity.hpp>
#include <sanguis/creator/geometry/texture_name.hpp>
#include <sge/parse/json/convert/to_enum.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/find_member_value_exn.hpp>
#include <sge/parse/json/int_type.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/string.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/text.hpp>


sanguis::creator::geometry::shape const
sanguis::creator::aux::generator::deserialization::shape(
	sge::parse::json::object const &_object
)
{
	return
		sanguis::creator::geometry::shape(
			sanguis::creator::aux::generator::deserialization::polygon(
				sge::parse::json::find_member_exn<
					sge::parse::json::array
				>(
					_object.members,
					FCPPT_TEXT("polygon")
				)
			),
			sge::parse::json::convert::to_enum<
				sanguis::creator::geometry::solidity::type
			>(
				sge::parse::json::find_member_value_exn(
					_object.members,
					FCPPT_TEXT("solidity")
				),
				sanguis::creator::geometry::solidity::size
			),
			fcppt::strong_typedef_construct_cast<
				sanguis::creator::geometry::depth
			>(
				sge::parse::json::find_member_exn<
					sge::parse::json::int_type
				>(
					_object.members,
					FCPPT_TEXT("depth")
				)
			),
			sanguis::creator::geometry::texture_name(
				sge::parse::json::find_member_exn<
					sge::parse::json::string
				>(
					_object.members,
					FCPPT_TEXT("texture_name")
				)
			)
		);
}
