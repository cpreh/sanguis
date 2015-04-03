#include <sanguis/model/optional_animation_sound.hpp>
#include <sanguis/model/impl/serialize/animation_sound.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/optional_member.hpp>
#include <fcppt/optional_bind_construct.hpp>
#include <fcppt/text.hpp>


sge::parse::json::optional_member
sanguis::model::impl::serialize::animation_sound(
	sanguis::model::optional_animation_sound const &_opt_sound
)
{
	return
		fcppt::optional_bind_construct(
			_opt_sound,
			[](
				sanguis::model::animation_sound const &_sound
			)
			{
				return
					sge::parse::json::member(
						FCPPT_TEXT("sound"),
						_sound.get()
					);
			}
		);
}
