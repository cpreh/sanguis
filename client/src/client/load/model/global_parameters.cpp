#include <sanguis/client/load/model/global_parameters.hpp>
#include <sanguis/client/load/resource/sounds_cref.hpp>
#include <sanguis/client/load/resource/sounds_fwd.hpp>
#include <sanguis/client/load/resource/textures_cref.hpp>
#include <sanguis/client/load/resource/textures_fwd.hpp>
#include <sanguis/model/cell_size.hpp>
#include <sanguis/model/optional_animation_delay.hpp>
#include <sanguis/model/optional_image_name.hpp>
#include <fcppt/copy.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::client::load::model::global_parameters::global_parameters(
	std::filesystem::path &&_path,
	sanguis::client::load::resource::textures_cref const _textures,
	sanguis::client::load::resource::sounds_cref const _sounds,
	sanguis::model::cell_size _cell_size,
	sanguis::model::optional_animation_delay const _delay,
	sanguis::model::optional_image_name &&_image
)
:
	path_(
		std::move(
			_path
		)
	),
	textures_(
		_textures
	),
	sounds_(
		_sounds
	),
	cell_size_(
		std::move(
			_cell_size
		)
	),
	delay_(
		_delay
	),
	image_(
		std::move(
			_image
		)
	)
{
}

std::filesystem::path const &
sanguis::client::load::model::global_parameters::path() const
{
	return
		path_;
}

sanguis::client::load::resource::textures const &
sanguis::client::load::model::global_parameters::textures() const
{
	return
		textures_.get();
}

sanguis::client::load::resource::sounds const &
sanguis::client::load::model::global_parameters::sounds() const
{
	return
		sounds_.get();
}

sanguis::model::cell_size const &
sanguis::client::load::model::global_parameters::cell_size() const
{
	return
		cell_size_;
}

sanguis::model::optional_animation_delay const &
sanguis::client::load::model::global_parameters::delay() const
{
	return
		delay_;
}

sanguis::model::optional_image_name const &
sanguis::client::load::model::global_parameters::image() const
{
	return
		image_;
}

sanguis::client::load::model::global_parameters
sanguis::client::load::model::global_parameters::new_image(
	sanguis::model::optional_image_name &&_image
) const
{
	return
		_image.has_value()
		?
			sanguis::client::load::model::global_parameters(
				fcppt::copy(
					this->path()
				),
				fcppt::make_cref(
					this->textures()
				),
				fcppt::make_cref(
					this->sounds()
				),
				this->cell_size(),
				this->delay(),
				std::move(
					_image
				)
		)
		:
			*this
		;
}
