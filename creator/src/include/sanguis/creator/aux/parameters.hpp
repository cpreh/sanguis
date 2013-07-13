#ifndef SANGUIS_CREATOR_AUX_PARAMETERS_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX_PARAMETERS_HPP_INCLUDED

#include <sanguis/creator/opening_count.hpp>
#include <sanguis/creator/aux/parameters_fwd.hpp>
#include <sanguis/creator/aux/randgen_fwd.hpp>
#include <fcppt/nonassignable.hpp>


namespace sanguis
{
namespace creator
{
namespace aux
{

class parameters
{
	FCPPT_NONASSIGNABLE(
		parameters
	);
public:
	parameters(
		sanguis::creator::aux::randgen &,
		sanguis::creator::opening_count
	);

	sanguis::creator::aux::randgen &
	randgen() const;

	sanguis::creator::opening_count const
	opening_count() const;
private:
	sanguis::creator::aux::randgen &randgen_;

	sanguis::creator::opening_count const opening_count_;
};

}
}
}

#endif
