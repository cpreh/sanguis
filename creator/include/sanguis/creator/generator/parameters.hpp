#ifndef SANGUIS_CREATOR_GENERATOR_PARAMETERS_HPP_INCLUDED
#define SANGUIS_CREATOR_GENERATOR_PARAMETERS_HPP_INCLUDED

#include <sanguis/creator/generator/opening_container.hpp>
#include <sanguis/creator/geometry/rect.hpp>
#include <sanguis/creator/symbol.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/nonassignable.hpp>

namespace sanguis
{
namespace creator
{
namespace generator
{

class parameters
{
	FCPPT_NONASSIGNABLE(
		parameters
	);
public:
	SANGUIS_CREATOR_SYMBOL
	parameters(
		geometry::rect const &,
		generator::opening_container const &
	);

	SANGUIS_CREATOR_SYMBOL
	geometry::rect const &
	area() const;

	SANGUIS_CREATOR_SYMBOL
	generator::opening_container const &
	openings() const;
private:
	geometry::rect const area_;

	generator::opening_container const openings_;
};

}
}
}

#endif
