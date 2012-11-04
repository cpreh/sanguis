#include <sanguis/creator/generator/name.hpp>
#include <sanguis/creator/generator/seed.hpp>
#include <sanguis/creator/generator/size.hpp>
#include <sanguis/creator/generator/top_parameters.hpp>


sanguis::creator::generator::top_parameters::top_parameters(
	sanguis::creator::generator::name const &_name,
	sanguis::creator::generator::seed const &_seed,
	sanguis::creator::generator::size const &_size
)
:
	name_(
		_name
	),
	seed_(
		_seed
	),
	size_(
		_size
	)
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
