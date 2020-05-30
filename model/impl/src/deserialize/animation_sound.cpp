#include <sanguis/model/animation_sound.hpp>
#include <sanguis/model/exception.hpp>
#include <sanguis/model/optional_animation_sound.hpp>
#include <sanguis/model/impl/deserialize/animation_sound.hpp>
#include <sge/charconv/utf8_string.hpp>
#include <sge/charconv/utf8_string_to_fcppt.hpp>
#include <sge/parse/json/find_member.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/to_exception.hpp>


sanguis::model::optional_animation_sound
sanguis::model::impl::deserialize::animation_sound(
	sge::parse::json::object const &_object
)
{
	return
		fcppt::optional::map(
			sge::parse::json::find_member<
				sge::charconv::utf8_string
			>(
				fcppt::make_cref(
					_object.members
				),
				"sound"
			),
			[](
				fcppt::reference<
					sge::charconv::utf8_string const
				> const &_value
			)
			{
				return
					sanguis::model::animation_sound{
						fcppt::optional::to_exception(
							sge::charconv::utf8_string_to_fcppt(
								_value.get()
							),
							[]{
								return
									sanguis::model::exception{
										FCPPT_TEXT("Failed to convert animation sound name")
									};
							}
						)
					};
			}
		);
}
