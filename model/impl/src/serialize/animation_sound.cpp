#include <sanguis/model/optional_animation_sound.hpp>
#include <sanguis/model/impl/serialize/animation_sound.hpp>
#include <sge/charconv/fcppt_string_to_utf8.hpp>
#include <sge/charconv/utf8_string.hpp>
#include <sge/parse/json/make_value.hpp>
#include <sge/parse/json/member.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/object_impl.hpp>


fcppt::optional::object<
	sge::parse::json::member
>
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
					sge::parse::json::member{
						sge::charconv::utf8_string{
							"sound"
						},
						sge::parse::json::make_value(
							sge::charconv::fcppt_string_to_utf8(
								_sound.get()
							)
						)
					};
			}
		);
}
