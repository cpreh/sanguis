#include "global_parameters.hpp"

sanguis::load::model::global_parameters::global_parameters(
	sge::filesystem::path const &path_,
	resource::textures const &textures_,
	sge::renderer::dim_type const &cell_size_,
	optional_delay const &delay_,
	optional_texture_identifier const &texture_)
:
	path_(path_),
	textures_(textures_),
	cell_size_(cell_size_),
	delay_(delay_),
	texture_(texture_)
{}

sge::filesystem::path const &
sanguis::load::model::global_parameters::path() const
{
	return path_;
}

sanguis::load::resource::textures const &
sanguis::load::model::global_parameters::textures() const
{
	return textures_;
}

sge::renderer::dim_type const &
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
	optional_texture_identifier const &ntex) const
{
	return ntex
		? global_parameters(
			path(),
			textures(),
			cell_size(),
			delay(),
			ntex
		)
		: *this;
}
