#include <sanguis/creator/generator/top_parameters.hpp>

sanguis::creator::generator::top_parameters::top_parameters(
	generator::name const &_name,
	generator::seed const &_seed,
	generator::size const &_size
)
:
	name_(_name),
	seed_(_seed),
	size_(_size)
{
}

sanguis::creator::generator::name const &
sanguis::creator::generator::top_parameters::name() const
{
	return name_;
}

sanguis::creator::generator::seed const
sanguis::creator::generator::top_parameters::seed() const
{
	return seed_;
}

sanguis::creator::generator::size const &
sanguis::creator::generator::top_parameters::size() const
{
	return size_;
}
