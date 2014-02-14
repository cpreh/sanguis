#ifndef SANGUIS_CREATOR_AUX__PARAMETERS_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX__PARAMETERS_HPP_INCLUDED

#include <sanguis/creator/opening_count.hpp>
#include <sanguis/creator/aux_/parameters_fwd.hpp>
#include <sanguis/creator/aux_/random/generator_fwd.hpp>
#include <fcppt/nonassignable.hpp>


namespace sanguis
{
namespace creator
{
namespace aux_
{

class parameters
{
	FCPPT_NONASSIGNABLE(
		parameters
	);
public:
	parameters(
		sanguis::creator::aux_::random::generator &,
		sanguis::creator::opening_count
	);

	sanguis::creator::aux_::random::generator &
	randgen() const;

	sanguis::creator::opening_count const
	opening_count() const;
private:
	sanguis::creator::aux_::random::generator &randgen_;

	sanguis::creator::opening_count const opening_count_;
};

}
}
}

#endif
