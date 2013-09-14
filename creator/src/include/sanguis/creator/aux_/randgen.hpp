#ifndef SANGUIS_CREATOR_AUX__RANDGEN_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX__RANDGEN_HPP_INCLUDED

#include <sanguis/creator/seed.hpp>
#include <sanguis/creator/aux_/rand_value.hpp>
#include <sanguis/creator/aux_/randgen_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/random/distribution/basic_decl.hpp>
#include <fcppt/random/distribution/parameters/uniform_int_decl.hpp>
#include <fcppt/random/generator/minstd_rand_decl.hpp>


namespace sanguis
{
namespace creator
{
namespace aux_
{

class randgen
{
	FCPPT_NONCOPYABLE(
		randgen
	);
public:
	explicit
	randgen(
		sanguis::creator::seed const &
	);

	~randgen();

	typedef sanguis::creator::aux_::rand_value result_type;

	sanguis::creator::aux_::randgen::result_type
	operator()();

	sanguis::creator::aux_::randgen::result_type
	min() const;

	sanguis::creator::aux_::randgen::result_type
	max() const;
private:
	fcppt::random::generator::minstd_rand generator_;

	typedef fcppt::random::distribution::basic<
		fcppt::random::distribution::parameters::uniform_int<
			sanguis::creator::aux_::randgen::result_type
		>
	> int_distribution;

	int_distribution distribution_;
};

}
}
}

#endif
