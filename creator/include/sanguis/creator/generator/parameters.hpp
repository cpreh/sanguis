#ifndef SANGUIS_CREATOR_GENERATOR_PARAMETERS_HPP_INCLUDED
#define SANGUIS_CREATOR_GENERATOR_PARAMETERS_HPP_INCLUDED

#include <sanguis/creator/symbol.hpp>
#include <sanguis/creator/generator/opening_container.hpp>
#include <sanguis/creator/generator/parameters_fwd.hpp>
#include <sanguis/creator/generator/randgen_fwd.hpp>
#include <sanguis/creator/geometry/rect.hpp>
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
		sanguis::creator::generator::randgen &,
		sanguis::creator::geometry::rect const &,
		sanguis::creator::generator::opening_container const &
	);

	SANGUIS_CREATOR_SYMBOL
	sanguis::creator::generator::randgen &
	randgen() const;

	SANGUIS_CREATOR_SYMBOL
	sanguis::creator::geometry::rect const &
	area() const;

	SANGUIS_CREATOR_SYMBOL
	sanguis::creator::generator::opening_container const &
	openings() const;
private:
	sanguis::creator::generator::randgen &randgen_;

	sanguis::creator::geometry::rect const area_;

	sanguis::creator::generator::opening_container const openings_;
};

}
}
}

#endif
