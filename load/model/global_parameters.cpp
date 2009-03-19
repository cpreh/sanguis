#include "global_parameters.hpp"

sanguis::load::model::global_parameters::global_parameters(
	sge::texture::part_ptr const tex_,
	sge::renderer::dim_type const &cell_size_,
	optional_delay const &delay_)
:
	tex_(tex_),
	cell_size_(cell_size_),
	delay_(delay_)
{}
	
sge::texture::part_ptr const
sanguis::load::model::global_parameters::tex() const
{
	return tex_;
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
