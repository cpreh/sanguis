#include "result.hpp"
#include "shape_container.hpp"
#include <sanguis/creator/generator/result.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/member_vector.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/text.hpp>

sge::parse::json::object const
sanguis::creator::generator::serialization::result(
	generator::result const &_result
)
{
	return
		sge::parse::json::object(
			fcppt::assign::make_container<
				sge::parse::json::member_vector
			>(
				sge::parse::json::member(
					FCPPT_TEXT("shapes"),
					serialization::shape_container(
						_result.shapes()
					)
				)
			)
			.container()
		);
}
