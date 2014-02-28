#include <sanguis/load/model/cell_size.hpp>
#include <sanguis/load/model/global_parameters.hpp>
#include <sanguis/load/resource/sounds_fwd.hpp>
#include <sanguis/load/resource/textures_fwd.hpp>
#include <sanguis/model/optional_animation_delay.hpp>
#include <sanguis/model/optional_image_name.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::load::model::global_parameters::global_parameters(
	boost::filesystem::path const &_path,
	sanguis::load::resource::textures const &_textures,
	sanguis::load::resource::sounds const &_sounds,
	sanguis::load::model::cell_size const &_cell_size,
	sanguis::model::optional_animation_delay const &_delay,
	sanguis::model::optional_image_name const &_image
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
	image_(
		_image
	)
{
}

boost::filesystem::path const &
sanguis::load::model::global_parameters::path() const
{
	return
		path_;
}

sanguis::load::resource::textures const &
sanguis::load::model::global_parameters::textures() const
{
	return
		textures_;
}

sanguis::load::resource::sounds const &
sanguis::load::model::global_parameters::sounds() const
{
	return
		sounds_;
}

sanguis::load::model::cell_size const &
sanguis::load::model::global_parameters::cell_size() const
{
	return
		cell_size_;
}

sanguis::model::optional_animation_delay const &
sanguis::load::model::global_parameters::delay() const
{
	return
		delay_;
}

sanguis::model::optional_image_name const &
sanguis::load::model::global_parameters::image() const
{
	return
		image_;
}

sanguis::load::model::global_parameters
sanguis::load::model::global_parameters::new_image(
	sanguis::model::optional_image_name const &_image
) const
{
	return
		_image
		?
			sanguis::load::model::global_parameters(
				this->path(),
				this->textures(),
				this->sounds(),
				this->cell_size(),
				this->delay(),
				_image
		)
		:
			*this
		;
}
