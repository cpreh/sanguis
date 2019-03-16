#include <sanguis/model/exception.hpp>
#include <sanguis/model/image_name.hpp>
#include <sanguis/model/optional_image_name.hpp>
#include <sanguis/model/impl/deserialize/image_name.hpp>
#include <sge/charconv/utf8_string.hpp>
#include <sge/charconv/utf8_string_to_fcppt.hpp>
#include <sge/parse/json/find_member.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/to_exception.hpp>


sanguis::model::optional_image_name
sanguis::model::impl::deserialize::image_name(
	sge::parse::json::object const &_object
)
{
	return
		fcppt::optional::map(
			sge::parse::json::find_member<
				sge::charconv::utf8_string
			>(
				_object.members,
				"texture"
			),
			[](
				fcppt::reference<
					sge::charconv::utf8_string const
				> const _texture_file
			)
			{
				return
					sanguis::model::image_name{
						fcppt::optional::to_exception(
							sge::charconv::utf8_string_to_fcppt(
								_texture_file.get()
							),
							[]{
								return
									sanguis::model::exception{
										FCPPT_TEXT("Failed to convert image name")
									};
							}
						)
					};
			}
		);
}
