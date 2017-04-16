#include <sanguis/model/animation_sound.hpp>
#include <sanguis/model/optional_animation_sound.hpp>
#include <sanguis/model/impl/deserialize/animation_sound.hpp>
#include <sge/parse/json/find_member.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/string.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/map.hpp>


sanguis::model::optional_animation_sound
sanguis::model::impl::deserialize::animation_sound(
	sge::parse::json::object const &_object
)
{
	return
		fcppt::optional::map(
			sge::parse::json::find_member<
				sge::parse::json::string
			>(
				_object.members,
				FCPPT_TEXT("sound")
			),
			[](
				fcppt::reference<
					sge::parse::json::string const
				> const &_value
			)
			{
				return
					sanguis::model::animation_sound{
						_value.get()
					};
			}
		);
}
