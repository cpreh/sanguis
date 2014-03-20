#include <sanguis/model/optional_animation_delay.hpp>
#include <sanguis/model/aux_/serialize/animation_delay.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/optional_member.hpp>
#include <sge/parse/json/convert/from_int.hpp>
#include <fcppt/optional_bind.hpp>
#include <fcppt/text.hpp>


sge::parse::json::optional_member
sanguis::model::aux_::serialize::animation_delay(
	sanguis::model::optional_animation_delay const &_opt_delay
)
{
	return
		fcppt::optional_bind(
			_opt_delay,
			[](
				sanguis::model::animation_delay const &_delay
			)
			{
				return
					sge::parse::json::member(
						FCPPT_TEXT("delay"),
						sge::parse::json::convert::from_int(
							_delay.get().count()
						)
					);
			}
		);
}
