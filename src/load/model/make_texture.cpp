#include <sanguis/exception.hpp>
#include <sanguis/load/model/find_texture.hpp>
#include <sanguis/load/model/global_parameters.hpp>
#include <sanguis/load/model/make_texture.hpp>
#include <sanguis/load/model/optional_texture_identifier.hpp>
#include <sanguis/load/resource/textures.hpp>
#include <sge/parse/json/object_fwd.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path_to_string.hpp>


sge::texture::const_part_shared_ptr
sanguis::load::model::make_texture(
	sge::parse::json::object const &_json_object,
	sanguis::load::model::global_parameters const &_param
)
{
	sanguis::load::model::optional_texture_identifier const texture_id(
		_param.new_texture(
			sanguis::load::model::find_texture(
				_json_object
			)
		).texture()
	);

	if(
		!texture_id
	)
		throw sanguis::exception(
			FCPPT_TEXT("texture not found in ")
			+
			fcppt::filesystem::path_to_string(
				_param.path()
			)
		);

	return
		_param.textures().load(
			_param.path()
			/
			texture_id->get()
		);
}
