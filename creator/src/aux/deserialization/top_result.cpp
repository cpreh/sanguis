#include <sanguis/creator/name.hpp>
#include <sanguis/creator/seed.hpp>
#include <sanguis/creator/top_result.hpp>
#include <sanguis/creator/aux/deserialization/grid.hpp>
#include <sanguis/creator/aux/deserialization/opening_container.hpp>
#include <sanguis/creator/aux/deserialization/top_result.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/int_type.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/string.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/text.hpp>


sanguis::creator::top_result
sanguis::creator::aux::deserialization::top_result(
	sge::parse::json::object const &_object
)
{
	return
		sanguis::creator::top_result(
			fcppt::strong_typedef_construct_cast<
				sanguis::creator::seed
			>(
				sge::parse::json::find_member_exn<
					sge::parse::json::int_type
				>(
					_object.members,
					FCPPT_TEXT("seed")
				)
			),
			sanguis::creator::name(
				sge::parse::json::find_member_exn<
					sge::parse::json::string
				>(
					_object.members,
					FCPPT_TEXT("name")
				)
			),
			sanguis::creator::aux::deserialization::grid(
				sge::parse::json::find_member_exn<
					sge::parse::json::object
				>(
					_object.members,
					FCPPT_TEXT("grid")
				)
			),
			sanguis::creator::aux::deserialization::opening_container(
				sge::parse::json::find_member_exn<
					sge::parse::json::array
				>(
					_object.members,
					FCPPT_TEXT("openings")
				)
			)
		);
}
