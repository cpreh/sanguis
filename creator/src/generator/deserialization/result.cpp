#include "result.hpp"
#include "shape_container.hpp"
#include <sanguis/creator/generator/name.hpp>
#include <sanguis/creator/generator/result.hpp>
#include <sanguis/creator/generator/seed.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/int_type.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/string.hpp>
#include <fcppt/text.hpp>

sanguis::creator::generator::result const
sanguis::creator::generator::deserialization::result(
	sge::parse::json::object const &_object
)
{
	return
		generator::result(
			deserialization::shape_container(
				sge::parse::json::find_member_exn<
					sge::parse::json::array
				>(
					_object.members,
					FCPPT_TEXT("shapes")
				)
			),
			generator::seed(
				sge::parse::json::find_member_exn<
					sge::parse::json::int_type
				>(
					_object.members,
					FCPPT_TEXT("seed")
				)
			),
			generator::name(
				sge::parse::json::find_member_exn<
					sge::parse::json::string
				>(
					_object.members,
					FCPPT_TEXT("name")
				)
			)
		);
}
