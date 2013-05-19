#ifndef SANGUIS_CREATOR_RANDGEN_HPP_INCLUDED
#define SANGUIS_CREATOR_RANDGEN_HPP_INCLUDED

#include <sanguis/creator/rand_value.hpp>
#include <sanguis/creator/seed.hpp>
#include <sanguis/creator/symbol.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/random/distribution/basic_decl.hpp>
#include <fcppt/random/distribution/parameters/uniform_int_decl.hpp>
#include <fcppt/random/generator/minstd_rand_decl.hpp>


namespace sanguis
{
namespace creator
{

class randgen
{
	FCPPT_NONCOPYABLE(
		randgen
	);
public:
	SANGUIS_CREATOR_SYMBOL
	explicit
	randgen(
		sanguis::creator::seed const &
	);

	SANGUIS_CREATOR_SYMBOL
	~randgen();

	typedef sanguis::creator::rand_value result_type;

	SANGUIS_CREATOR_SYMBOL
	sanguis::creator::randgen::result_type
	operator()();

	SANGUIS_CREATOR_SYMBOL
	sanguis::creator::randgen::result_type
	min() const;

	SANGUIS_CREATOR_SYMBOL
	sanguis::creator::randgen::result_type
	max() const;
private:
	fcppt::random::generator::minstd_rand generator_;

	typedef fcppt::random::distribution::basic<
		fcppt::random::distribution::parameters::uniform_int<
			sanguis::creator::randgen::result_type
		>
	> int_distribution;

	int_distribution distribution_;
};

}
}

#endif
