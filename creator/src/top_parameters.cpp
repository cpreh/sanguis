#include <sanguis/creator/name.hpp>
#include <sanguis/creator/seed.hpp>
#include <sanguis/creator/top_parameters.hpp>


sanguis::creator::top_parameters::top_parameters(
	sanguis::creator::name const &_name,
	sanguis::creator::seed const &_seed
)
:
	name_(
		_name
	),
	seed_(
		_seed
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
