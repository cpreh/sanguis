#ifndef SANGUIS_CREATOR_IMPL_RANDOM_UNIFORM_INT_DISTRIBUTION_DECL_HPP_INCLUDED
#define SANGUIS_CREATOR_IMPL_RANDOM_UNIFORM_INT_DISTRIBUTION_DECL_HPP_INCLUDED

#include <sanguis/creator/impl/random/generator_fwd.hpp>
#include <sanguis/creator/impl/random/uniform_int_distribution_fwd.hpp>


namespace sanguis
{
namespace creator
{
namespace impl
{
namespace random
{

template<
	typename IntType
>
class uniform_int_distribution
{
public:
	typedef
	IntType
	result_type;

	class param_type
	{
	public:
		param_type(
			IntType min,
			IntType max
		);

		IntType
		min() const;

		IntType
		max() const;
	private:
		IntType min_;

		IntType max_;
	};

	explicit
	uniform_int_distribution(
		param_type const &
	);

	result_type
	operator()(
		sanguis::creator::impl::random::generator &
	);
private:
	IntType min_;

	IntType max_;
};

}
}
}
}

#endif
