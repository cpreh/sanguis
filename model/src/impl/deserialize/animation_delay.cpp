#include <sanguis/model/animation_delay.hpp>
#include <sanguis/model/optional_animation_delay.hpp>
#include <sanguis/model/impl/deserialize/animation_delay.hpp>
#include <sge/parse/json/find_member.hpp>
#include <sge/parse/json/int_type.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/optional_map.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <fcppt/config/external_end.hpp>


sanguis::model::optional_animation_delay
sanguis::model::impl::deserialize::animation_delay(
	sge::parse::json::object const &_object
)
{
	return
		fcppt::optional_map(
			sge::parse::json::find_member<
				sge::parse::json::int_type
			>(
				_object.members,
				FCPPT_TEXT("delay")
			),
			[](
				sge::parse::json::int_type const _value
			)
			{
				return
					sanguis::model::animation_delay{
						std::chrono::milliseconds{
							_value
						}
					};
			}
		);
}
