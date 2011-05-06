#include "result.hpp"
#include "shape_container.hpp"
#include <sanguis/creator/generator/result.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/object.hpp>
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
			)
		);
}
