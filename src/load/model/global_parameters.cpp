#include <sanguis/load/model/global_parameters.hpp>

sanguis::load::model::global_parameters::global_parameters(
	fcppt::filesystem::path const &_path,
	resource::textures const &_textures,
	sge::renderer::dim2 const &_cell_size,
	optional_delay const &_delay,
	optional_texture_identifier const &_texture,
	resource::sounds const &_sounds
)
:
	path_(_path),
	textures_(_textures),
	cell_size_(_cell_size),
	delay_(_delay),
	texture_(_texture),
	sounds_(_sounds)
{}

fcppt::filesystem::path const &
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
	optional_texture_identifier const &_tex
) const
{
	return
		_tex
		?
			model::global_parameters(
				this->path(),
				this->textures(),
				this->cell_size(),
				this->delay(),
				_tex,
				this->sounds()
		)
		:
			*this
		;
}

sanguis::load::resource::sounds const &
sanguis::load::model::global_parameters::sounds() const
{
	return sounds_;
}
