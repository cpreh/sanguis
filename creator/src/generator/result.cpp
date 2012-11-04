#include <sanguis/creator/generator/name.hpp>
#include <sanguis/creator/generator/seed.hpp>
#include <sanguis/creator/generator/size.hpp>
#include <sanguis/creator/generator/result.hpp>
#include <sanguis/creator/geometry/shape_container.hpp>


sanguis::creator::generator::result::result(
	sanguis::creator::geometry::shape_container const &_shapes,
	sanguis::creator::generator::seed const &_seed,
	sanguis::creator::generator::name const &_name,
	sanguis::creator::generator::size const &_size
)
:
	shapes_(
		_shapes
	),
	seed_(
		_seed
	),
	name_(
		_name
	),
	size_(
		_size
	)
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

sanguis::creator::generator::size const &
sanguis::creator::generator::result::size() const
{
	return size_;
}
