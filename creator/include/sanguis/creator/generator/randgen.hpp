#ifndef SANGUIS_CREATOR_GENERATOR_RANDGEN_HPP_INCLUDED
#define SANGUIS_CREATOR_GENERATOR_RANDGEN_HPP_INCLUDED

#include <sanguis/creator/generator/rand_value.hpp>
#include <sanguis/creator/generator/seed.hpp>
#include <sanguis/creator/symbol.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/random/distribution/uniform_int_decl.hpp>
#include <fcppt/random/generator/minstd_rand_decl.hpp>


namespace sanguis
{
namespace creator
{
namespace generator
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
		sanguis::creator::generator::seed const &
	);

	SANGUIS_CREATOR_SYMBOL
	~randgen();

	typedef sanguis::creator::generator::rand_value result_type;

	SANGUIS_CREATOR_SYMBOL
	sanguis::creator::generator::randgen::result_type const
	operator()();

	SANGUIS_CREATOR_SYMBOL
	sanguis::creator::generator::randgen::result_type const
	min() const;

	SANGUIS_CREATOR_SYMBOL
	sanguis::creator::generator::randgen::result_type const
	max() const;
private:
	fcppt::random::generator::minstd_rand generator_;

	typedef fcppt::random::distribution::uniform_int<
		sanguis::creator::generator::randgen::result_type::value_type
	> int_distribution;

	int_distribution distribution_;
};

}
}
}

#endif
