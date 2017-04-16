#ifndef SANGUIS_CREATOR_IMPL_RANDOM_GENERATOR_HPP_INCLUDED
#define SANGUIS_CREATOR_IMPL_RANDOM_GENERATOR_HPP_INCLUDED

#include <sanguis/creator/seed.hpp>
#include <sanguis/creator/impl/random/generator_fwd.hpp>
#include <sanguis/creator/impl/random/value.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/random/generator/mt19937_decl.hpp>


namespace sanguis
{
namespace creator
{
namespace impl
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

	typedef sanguis::creator::impl::random::value result_type;

	sanguis::creator::impl::random::generator::result_type
	operator()();

	static
	sanguis::creator::impl::random::generator::result_type
	min();

	static
	sanguis::creator::impl::random::generator::result_type
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
