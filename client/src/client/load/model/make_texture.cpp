#include <sanguis/exception.hpp>
#include <sanguis/client/load/model/global_parameters.hpp>
#include <sanguis/client/load/model/make_texture.hpp>
#include <sanguis/client/load/resource/textures.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path_to_string.hpp>


sge::texture::part const &
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
