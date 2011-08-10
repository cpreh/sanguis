#ifndef SANGUIS_CREATOR_GENERATOR_RESULT_HPP_INCLUDED
#define SANGUIS_CREATOR_GENERATOR_RESULT_HPP_INCLUDED

#include <sanguis/creator/generator/result_fwd.hpp>
#include <sanguis/creator/generator/name.hpp>
#include <sanguis/creator/generator/seed.hpp>
#include <sanguis/creator/generator/size.hpp>
#include <sanguis/creator/geometry/shape_container.hpp>
#include <sanguis/creator/symbol.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/nonassignable.hpp>

namespace sanguis
{
namespace creator
{
namespace generator
{

class result
{
	FCPPT_NONASSIGNABLE(
		result
	);
public:
	result(
		geometry::shape_container const &,
		generator::seed const &,
		generator::name const &,
		generator::size const &
	);

	SANGUIS_CREATOR_SYMBOL
	geometry::shape_container const &
	shapes() const;

	SANGUIS_CREATOR_SYMBOL
	generator::seed const
	seed() const;

	SANGUIS_CREATOR_SYMBOL
	generator::name const &
	name() const;

	SANGUIS_CREATOR_SYMBOL
	generator::size const &
	size() const;
private:
	geometry::shape_container const shapes_;

	generator::seed const seed_;

	generator::name const name_;

	generator::size const size_;
};

}
}
}

#endif
