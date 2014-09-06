#include <sanguis/creator/enemy_kind.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/spawn.hpp>
#include <sanguis/creator/spawn_pos.hpp>
#include <sanguis/creator/spawn_type.hpp>
#include <sanguis/creator/aux_/deserialization/spawn.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/find_member_value_exn.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/convert/to_enum.hpp>
#include <sge/parse/json/convert/to_static_container.hpp>
#include <fcppt/enum_max_value.hpp>
#include <fcppt/text.hpp>


sanguis::creator::spawn
sanguis::creator::aux_::deserialization::spawn(
	sge::parse::json::object const &_object
)
{
	return
		sanguis::creator::spawn(
			sanguis::creator::spawn_pos(
				sge::parse::json::convert::to_static_container<
					sanguis::creator::pos
				>(
					sge::parse::json::find_member_exn<
						sge::parse::json::array
					>(
						_object.members,
						FCPPT_TEXT("pos")
					)
				)
			),
			sge::parse::json::convert::to_enum<
				sanguis::creator::enemy_type
			>(
				sge::parse::json::find_member_value_exn(
					_object.members,
					FCPPT_TEXT("enemy_type")
				),
				fcppt::enum_max_value<
					sanguis::creator::enemy_type
				>::value
			),
			sge::parse::json::convert::to_enum<
				sanguis::creator::spawn_type
			>(
				sge::parse::json::find_member_value_exn(
					_object.members,
					FCPPT_TEXT("spawn_type")
				),
				fcppt::enum_max_value<
					sanguis::creator::spawn_type
				>::value
			),
			sge::parse::json::convert::to_enum<
				sanguis::creator::enemy_kind
			>(
				sge::parse::json::find_member_value_exn(
					_object.members,
					FCPPT_TEXT("enemy_kind")
				),
				fcppt::enum_max_value<
					sanguis::creator::enemy_kind
				>::value
			)
		);
}
