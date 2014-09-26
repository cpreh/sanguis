#include <sanguis/creator/destructible.hpp>
#include <sanguis/creator/destructible_pos.hpp>
#include <sanguis/creator/destructible_type.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/aux_/deserialization/destructible.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/find_member_value_exn.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/convert/to_enum.hpp>
#include <sge/parse/json/convert/to_static_container.hpp>
#include <fcppt/enum_max_value.hpp>
#include <fcppt/text.hpp>


sanguis::creator::destructible
sanguis::creator::aux_::deserialization::destructible(
	sge::parse::json::object const &_object
)
{
	return
		sanguis::creator::destructible(
			sanguis::creator::destructible_pos(
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
				sanguis::creator::destructible_type
			>(
				sge::parse::json::find_member_value_exn(
					_object.members,
					FCPPT_TEXT("type")
				),
				fcppt::enum_max_value<
					sanguis::creator::destructible_type
				>::value
			)
		);
}
