#include <sanguis/exception.hpp>
#include <sanguis/client/load/model/global_parameters.hpp>
#include <sanguis/client/load/model/make_texture.hpp>
#include <sanguis/client/load/resource/textures.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path_to_string.hpp>


sge::texture::const_part_shared_ptr
sanguis::client::load::model::make_texture(
	sanguis::client::load::model::global_parameters const &_parameters
)
{
	if(
		!_parameters.image()
	)
		throw
			sanguis::exception(
				FCPPT_TEXT("texture not found in ")
				+
				fcppt::filesystem::path_to_string(
					_parameters.path()
				)
			);

	return
		_parameters.textures().load(
			_parameters.path()
			/
			_parameters.image()->get()
		);
}
