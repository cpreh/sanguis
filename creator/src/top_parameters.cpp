#include <sanguis/creator/name.hpp>
#include <sanguis/creator/seed.hpp>
#include <sanguis/creator/size.hpp>
#include <sanguis/creator/top_parameters.hpp>


sanguis::creator::top_parameters::top_parameters(
	sanguis::creator::name const &_name,
	sanguis::creator::seed const &_seed,
	sanguis::creator::size const &_size
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

sanguis::creator::name const &
sanguis::creator::top_parameters::name() const
{
	return name_;
}

sanguis::creator::seed const
sanguis::creator::top_parameters::seed() const
{
	return seed_;
}

sanguis::creator::size const &
sanguis::creator::top_parameters::size() const
{
	return size_;
}
