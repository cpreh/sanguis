#ifndef SANGUIS_CREATOR_AUX__RANDOM_GENERATOR_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX__RANDOM_GENERATOR_HPP_INCLUDED

#include <sanguis/creator/seed.hpp>
#include <sanguis/creator/aux_/random/generator_fwd.hpp>
#include <sanguis/creator/aux_/random/value.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/random/generator/mt19937_decl.hpp>


namespace sanguis
{
namespace creator
{
namespace aux_
{
namespace random
{

class generator
{
	FCPPT_NONCOPYABLE(
		generator
	);
public:
	explicit
	generator(
		sanguis::creator::seed const &
	);

	~generator();

	typedef sanguis::creator::aux_::random::value result_type;

	sanguis::creator::aux_::random::generator::result_type
	operator()();

	static
	sanguis::creator::aux_::random::generator::result_type
	min();

	static
	sanguis::creator::aux_::random::generator::result_type
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
}

#endif
