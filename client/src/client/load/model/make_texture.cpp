#include <sanguis/exception.hpp>
#include <sanguis/client/load/model/global_parameters.hpp>
#include <sanguis/client/load/model/make_texture.hpp>
#include <sanguis/client/load/resource/textures.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/optional/to_exception.hpp>


sge::texture::part const &
sanguis::client::load::model::make_texture(
	sanguis::client::load::model::global_parameters const &_parameters
)
{
	return
		_parameters.textures().load(
			_parameters.path()
			/
			fcppt::optional::to_exception(
				_parameters.image(),
				[
					&_parameters
				]{
					return
						sanguis::exception(
							FCPPT_TEXT("texture not found in ")
							+
							fcppt::filesystem::path_to_string(
								_parameters.path()
							)
						);
				}
			).get()
		);
}
