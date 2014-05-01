#include <sanguis/creator/destructible.hpp>
#include <sanguis/creator/aux_/serialization/destructible.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/convert/from_container.hpp>
#include <sge/parse/json/convert/from_enum.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>


sge::parse::json::object
sanguis::creator::aux_::serialization::destructible(
	sanguis::creator::destructible const &_destructible
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
						_destructible.pos().get()
					)
				)
			)(
				sge::parse::json::member(
					FCPPT_TEXT("type"),
					sge::parse::json::convert::from_enum(
						_destructible.type()
					)
				)
			)
		);
}
