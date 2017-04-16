#include <sanguis/model/optional_animation_delay.hpp>
#include <sanguis/model/impl/serialize/animation_delay.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/optional_member.hpp>
#include <sge/parse/json/value.hpp>
#include <sge/parse/json/convert/from_int.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/map.hpp>


sge::parse::json::optional_member
sanguis::model::impl::serialize::animation_delay(
	sanguis::model::optional_animation_delay const &_opt_delay
)
{
	return
		fcppt::optional::map(
			_opt_delay,
			[](
				sanguis::model::animation_delay const &_delay
			)
			{
				return
					sge::parse::json::member(
						FCPPT_TEXT("delay"),
						sge::parse::json::value(
							sge::parse::json::convert::from_int(
								_delay.get().count()
							)
						)
					);
			}
		);
}
