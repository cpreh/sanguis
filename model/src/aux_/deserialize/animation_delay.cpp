#include <sanguis/model/animation_delay.hpp>
#include <sanguis/model/optional_animation_delay.hpp>
#include <sanguis/model/aux_/deserialize/animation_delay.hpp>
#include <sge/parse/json/find_member.hpp>
#include <sge/parse/json/int_type.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <fcppt/config/external_end.hpp>


sanguis::model::optional_animation_delay const
sanguis::model::aux_::deserialize::animation_delay(
	sge::parse::json::object const &_object
)
{
	typedef
	fcppt::optional<
		sge::parse::json::int_type
	>
	optional_int_type;

	optional_int_type const result{
		sge::parse::json::find_member<
			sge::parse::json::int_type
		>(
			_object.members,
			FCPPT_TEXT("delay")
		)
	};

	return
		result
		?
			sanguis::model::optional_animation_delay{
				sanguis::model::animation_delay{
					std::chrono::milliseconds{
						*result
					}
				}
			}
		:
			sanguis::model::optional_animation_delay{}
		;
}
