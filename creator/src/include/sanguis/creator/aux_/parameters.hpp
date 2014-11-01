#ifndef SANGUIS_CREATOR_AUX__PARAMETERS_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX__PARAMETERS_HPP_INCLUDED

#include <sanguis/creator/opening_count_array.hpp>
#include <sanguis/creator/spawn_boss.hpp>
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
		sanguis::creator::spawn_boss,
		sanguis::creator::opening_count_array
	);

	sanguis::creator::aux_::random::generator &
	randgen() const;

	sanguis::creator::spawn_boss const
	spawn_boss() const;

	sanguis::creator::opening_count_array const
	opening_count_array() const;
private:
	sanguis::creator::aux_::random::generator &randgen_;

	sanguis::creator::spawn_boss const spawn_boss_;

	sanguis::creator::opening_count_array const opening_count_array_;
};

}
}
}

#endif
