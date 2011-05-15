#include <sanguis/creator/generator/result.hpp>

sanguis::creator::generator::result::result(
	geometry::shape_container const &_shapes,
	generator::seed const &_seed,
	generator::name const &_name
)
:
	shapes_(_shapes),
	seed_(_seed),
	name_(_name)
{
}

sanguis::creator::geometry::shape_container const &
sanguis::creator::generator::result::shapes() const
{
	return shapes_;
}

sanguis::creator::generator::seed const
sanguis::creator::generator::result::seed() const
{
	return seed_;
}

sanguis::creator::generator::name const &
sanguis::creator::generator::result::name() const
{
	return name_;
}
