#include <sanguis/creator/top_result.hpp>
#include <sanguis/creator/aux/serialization/background_grid.hpp>
#include <sanguis/creator/aux/serialization/grid.hpp>
#include <sanguis/creator/aux/serialization/opening_container.hpp>
#include <sanguis/creator/aux/serialization/spawn_container.hpp>
#include <sanguis/creator/aux/serialization/top_result.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/int_type.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/string.hpp>
#include <sge/parse/json/convert/from_int.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>


sge::parse::json::object
sanguis::creator::aux::serialization::top_result(
	sanguis::creator::top_result const &_result
)
{
	return
		sge::parse::json::object(
			// Use make_container until boost::unordered_map detects initializer lists for clang
			fcppt::assign::make_container<
				sge::parse::json::member_map
			>(
				sge::parse::json::member(
					FCPPT_TEXT("seed"),
					sge::parse::json::convert::from_int(
						_result.seed().get()
					)
				)
			)(
				sge::parse::json::member(
					FCPPT_TEXT("name"),
					sge::parse::json::string(
						_result.name().get()
					)
				)
			)(
				sge::parse::json::member(
					FCPPT_TEXT("grid"),
					sanguis::creator::aux::serialization::grid(
						_result.grid()
					)
				)
			)(
				sge::parse::json::member(
					FCPPT_TEXT("background_grid"),
					sanguis::creator::aux::serialization::background_grid(
						_result.background_grid()
					)
				)
			)(
				sge::parse::json::member(
					FCPPT_TEXT("openings"),
					sanguis::creator::aux::serialization::opening_container(
						_result.openings()
					)
				)
			)(
				sge::parse::json::member(
					FCPPT_TEXT("spawns"),
					sanguis::creator::aux::serialization::spawn_container(
						_result.spawns()
					)
				)
			)
		);
}
