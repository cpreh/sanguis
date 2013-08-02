#include <sanguis/creator/spawn.hpp>
#include <sanguis/creator/aux/serialization/spawn.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/convert/from_container.hpp>
#include <sge/parse/json/convert/from_enum.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>


sge::parse::json::object
sanguis::creator::aux::serialization::spawn(
	sanguis::creator::spawn const &_spawn
)
{
	return
		sge::parse::json::object(
			fcppt::assign::make_container<
				sge::parse::json::member_map
			>(
				sge::parse::json::member(
					FCPPT_TEXT("pos"),
					sge::parse::json::convert::from_container(
						_spawn.pos().get()
					)
				)
			)(
				sge::parse::json::member(
					FCPPT_TEXT("enemy_type"),
					sge::parse::json::convert::from_enum(
						_spawn.enemy_type()
					)
				)
			)(
				sge::parse::json::member(
					FCPPT_TEXT("spawn_type"),
					sge::parse::json::convert::from_enum(
						_spawn.spawn_type()
					)
				)
			)
		);
}
