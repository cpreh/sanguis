#include <sanguis/model/optional_animation_sound.hpp>
#include <sanguis/model/impl/serialize/animation_sound.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/optional_member.hpp>
#include <sge/parse/json/value.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/map.hpp>


sge::parse::json::optional_member
sanguis::model::impl::serialize::animation_sound(
	sanguis::model::optional_animation_sound const &_opt_sound
)
{
	return
		fcppt::optional::map(
			_opt_sound,
			[](
				sanguis::model::animation_sound const &_sound
			)
			{
				return
					sge::parse::json::member(
						FCPPT_TEXT("sound"),
						sge::parse::json::value(
							_sound.get()
						)
					);
			}
		);
}
