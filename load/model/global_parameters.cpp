#include "global_parameters.hpp"

sanguis::load::model::global_parameters::global_parameters(
	sge::renderer::dim_type const &cell_size_,
	optional_delay const &delay_)
:
	cell_size_(cell_size_),
	delay_(delay_)
{}
	
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
