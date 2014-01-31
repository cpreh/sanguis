#ifndef SANGUIS_CREATOR_AUX__RANDGEN_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX__RANDGEN_HPP_INCLUDED

#include <sanguis/creator/seed.hpp>
#include <sanguis/creator/aux_/rand_value.hpp>
#include <sanguis/creator/aux_/randgen_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/random/generator/mt19937_decl.hpp>


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

	static
	sanguis::creator::aux_::randgen::result_type
	min();

	static
	sanguis::creator::aux_::randgen::result_type
	max();
private:
	typedef
	fcppt::random::generator::mt19937
	generator_type;

	generator_type generator_;
};

}
}
}

#endif
