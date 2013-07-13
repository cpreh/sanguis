#include <sanguis/creator/name.hpp>
#include <sanguis/creator/opening_count.hpp>
#include <sanguis/creator/seed.hpp>
#include <sanguis/creator/top_parameters.hpp>


sanguis::creator::top_parameters::top_parameters(
	sanguis::creator::name const &_name,
	sanguis::creator::seed const &_seed,
	sanguis::creator::opening_count const _opening_count
)
:
	name_(
		_name
	),
	seed_(
		_seed
	),
	opening_count_(
		_opening_count
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

sanguis::creator::opening_count const
sanguis::creator::top_parameters::opening_count() const
{
	return opening_count_;
}
