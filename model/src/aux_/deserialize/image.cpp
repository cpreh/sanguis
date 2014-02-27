#include <sanguis/model/optional_image.hpp>
#include <sanguis/model/aux_/deserialize/image.hpp>
#include <sanguis/model/aux_/deserialize/parameters.hpp>
#include <sge/image2d/load_exn.hpp>
#include <sge/parse/json/find_member.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/string.hpp>
#include <fcppt/optional_bind.hpp>
#include <fcppt/text.hpp>


sanguis::model::optional_image
sanguis::model::aux_::deserialize::image(
	sanguis::model::aux_::deserialize::parameters const &_parameters,
	sge::parse::json::object const &_object
)
{
	return
		fcppt::optional_bind(
			sge::parse::json::find_member<
				sge::parse::json::string
			>(
				_object.members,
				FCPPT_TEXT("texture")
			),
			[
				&_parameters
			](
				sge::parse::json::string const &_texture_file
			)
			{
				return
					sge::image2d::load_exn(
						_parameters.image_system(),
						_parameters.dir_path()
						/
						_texture_file
					);
			}
		);
}
