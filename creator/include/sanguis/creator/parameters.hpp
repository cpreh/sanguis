#ifndef SANGUIS_CREATOR_PARAMETERS_HPP_INCLUDED
#define SANGUIS_CREATOR_PARAMETERS_HPP_INCLUDED

#include <sanguis/creator/opening_container.hpp>
#include <sanguis/creator/parameters_fwd.hpp>
#include <sanguis/creator/randgen_fwd.hpp>
#include <sanguis/creator/size.hpp>
#include <sanguis/creator/symbol.hpp>
#include <fcppt/nonassignable.hpp>


namespace sanguis
{
namespace creator
{

class parameters
{
	FCPPT_NONASSIGNABLE(
		parameters
	);
public:
	SANGUIS_CREATOR_SYMBOL
	parameters(
		sanguis::creator::randgen &,
		sanguis::creator::size const &,
		sanguis::creator::opening_container const &
	);

	SANGUIS_CREATOR_SYMBOL
	sanguis::creator::randgen &
	randgen() const;

	SANGUIS_CREATOR_SYMBOL
	sanguis::creator::size const &
	size() const;

	SANGUIS_CREATOR_SYMBOL
	sanguis::creator::opening_container const &
	openings() const;
private:
	sanguis::creator::randgen &randgen_;

	sanguis::creator::size const size_;

	sanguis::creator::opening_container const openings_;
};

}
}

#endif
