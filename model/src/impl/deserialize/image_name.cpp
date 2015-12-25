#include <sanguis/model/image_name.hpp>
#include <sanguis/model/optional_image_name.hpp>
#include <sanguis/model/impl/deserialize/image_name.hpp>
#include <sge/parse/json/find_member.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/string.hpp>
#include <fcppt/optional_map.hpp>
#include <fcppt/text.hpp>


sanguis::model::optional_image_name
sanguis::model::impl::deserialize::image_name(
	sge::parse::json::object const &_object
)
{
	return
		fcppt::optional_map(
			sge::parse::json::find_member<
				sge::parse::json::string
			>(
				_object.members,
				FCPPT_TEXT("texture")
			),
			[](
				sge::parse::json::string const &_texture_file
			)
			{
				return
					sanguis::model::image_name(
						_texture_file
					);
			}
		);
}
