#include <sanguis/creator/aux/generator/deserialization/result.hpp>
#include <sanguis/creator/aux/generator/deserialization/shape_container.hpp>
#include <sanguis/creator/generator/name.hpp>
#include <sanguis/creator/generator/result.hpp>
#include <sanguis/creator/generator/seed.hpp>
#include <sanguis/creator/generator/size.hpp>
#include <sge/parse/json/convert/to_static_container.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/int_type.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/string.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/text.hpp>


sanguis::creator::generator::result const
sanguis::creator::aux::generator::deserialization::result(
	sge::parse::json::object const &_object
)
{
	return
		sanguis::creator::generator::result(
			sanguis::creator::aux::generator::deserialization::shape_container(
				sge::parse::json::find_member_exn<
					sge::parse::json::array
				>(
					_object.members,
					FCPPT_TEXT("shapes")
				)
			),
			fcppt::strong_typedef_construct_cast<
				sanguis::creator::generator::seed
			>(
				sge::parse::json::find_member_exn<
					sge::parse::json::int_type
				>(
					_object.members,
					FCPPT_TEXT("seed")
				)
			),
			sanguis::creator::generator::name(
				sge::parse::json::find_member_exn<
					sge::parse::json::string
				>(
					_object.members,
					FCPPT_TEXT("name")
				)
			),
			sge::parse::json::convert::to_static_container<
				sanguis::creator::generator::size
			>(
				sge::parse::json::find_member_exn<
					sge::parse::json::array
				>(
					_object.members,
					FCPPT_TEXT("size")
				)
			)
		);
}
