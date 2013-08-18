#include <sanguis/load/model/cell_size.hpp>
#include <sanguis/load/model/global_parameters.hpp>
#include <sanguis/load/model/optional_delay.hpp>
#include <sanguis/load/model/optional_texture_identifier.hpp>
#include <sanguis/load/resource/sounds_fwd.hpp>
#include <sanguis/load/resource/textures_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::load::model::global_parameters::global_parameters(
	boost::filesystem::path const &_path,
	sanguis::load::resource::textures const &_textures,
	sanguis::load::resource::sounds const &_sounds,
	sanguis::load::model::cell_size const &_cell_size,
	sanguis::load::model::optional_delay const &_delay,
	sanguis::load::model::optional_texture_identifier const &_texture
)
:
	path_(
		_path
	),
	textures_(
		_textures
	),
	sounds_(
		_sounds
	),
	cell_size_(
		_cell_size
	),
	delay_(
		_delay
	),
	texture_(
		_texture
	)
{
}

boost::filesystem::path const &
sanguis::load::model::global_parameters::path() const
{
	return path_;
}

sanguis::load::resource::textures const &
sanguis::load::model::global_parameters::textures() const
{
	return textures_;
}

sanguis::load::resource::sounds const &
sanguis::load::model::global_parameters::sounds() const
{
	return sounds_;
}

sanguis::load::model::cell_size const &
sanguis::load::model::global_parameters::cell_size() const
{
	return cell_size_;
}

sanguis::load::model::optional_delay const &
sanguis::load::model::global_parameters::delay() const
{
	return delay_;
}

sanguis::load::model::optional_texture_identifier const &
sanguis::load::model::global_parameters::texture() const
{
	return texture_;
}

sanguis::load::model::global_parameters const
sanguis::load::model::global_parameters::new_texture(
	sanguis::load::model::optional_texture_identifier const &_tex
) const
{
	return
		_tex
		?
			sanguis::load::model::global_parameters(
				this->path(),
				this->textures(),
				this->sounds(),
				this->cell_size(),
				this->delay(),
				_tex
		)
		:
			*this
		;
}
