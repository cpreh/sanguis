#include "result.hpp"
#include "shape_container.hpp"
#include <sanguis/creator/generator/result.hpp>
#include <sge/parse/json/convert/from_container.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/int_type.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/member_vector.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/string.hpp>
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
			(
				sge::parse::json::member(
					FCPPT_TEXT("seed"),
					static_cast<
						sge::parse::json::int_type
					>(
						_result.seed().get()
					)
				)
			)
			(
				sge::parse::json::member(
					FCPPT_TEXT("name"),
					sge::parse::json::string(
						_result.name().get()
					)
				)
			)
			(
				sge::parse::json::member(
					FCPPT_TEXT("size"),
					sge::parse::json::convert::from_container(
						_result.size()
					)
				)
			)
			.container()
		);
}
