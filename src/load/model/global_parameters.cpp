#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/load/model/global_parameters.hpp>
#include <sanguis/load/model/optional_delay.hpp>
#include <sanguis/load/model/optional_texture_identifier.hpp>
#include <sanguis/load/resource/textures_fwd.hpp>
#include <sge/renderer/dim2.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::load::model::global_parameters::global_parameters(
	sanguis::random_generator &_random_generator,
	boost::filesystem::path const &_path,
	sanguis::load::resource::textures const &_textures,
	sge::renderer::dim2 const &_cell_size,
	sanguis::load::model::optional_delay const &_delay,
	sanguis::load::model::optional_texture_identifier const &_texture
)
:
	random_generator_(
		_random_generator
	),
	path_(
		_path
	),
	textures_(
		_textures
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

sanguis::random_generator &
sanguis::load::model::global_parameters::random_generator() const
{
	return random_generator_;
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

sge::renderer::dim2 const &
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
				this->random_generator(),
				this->path(),
				this->textures(),
				this->cell_size(),
				this->delay(),
				_tex
		)
		:
			*this
		;
}
