#include <sanguis/model/animation_sound.hpp>
#include <sanguis/model/optional_animation_sound.hpp>
#include <sanguis/model/impl/deserialize/animation_sound.hpp>
#include <sge/parse/json/find_member.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/string.hpp>
#include <fcppt/optional_map.hpp>
#include <fcppt/text.hpp>


sanguis::model::optional_animation_sound
sanguis::model::impl::deserialize::animation_sound(
	sge::parse::json::object const &_object
)
{
	return
		fcppt::optional_map(
			sge::parse::json::find_member<
				sge::parse::json::string
			>(
				_object.members,
				FCPPT_TEXT("sound")
			),
			[](
				sge::parse::json::string const &_value
			)
			{
				return
					sanguis::model::animation_sound{
						_value
					};
			}
		);
}
