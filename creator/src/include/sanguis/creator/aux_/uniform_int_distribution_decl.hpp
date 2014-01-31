#ifndef SANGUIS_CREATOR_AUX__UNIFORM_INT_DISTRIBUTION_DECL_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX__UNIFORM_INT_DISTRIBUTION_DECL_HPP_INCLUDED

#include <sanguis/creator/aux_/randgen_fwd.hpp>
#include <sanguis/creator/aux_/uniform_int_distribution_fwd.hpp>


namespace sanguis
{
namespace creator
{
namespace aux_
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
		sanguis::creator::aux_::randgen &
	);
private:
	IntType min_;

	IntType max_;
};

}
}
}

#endif
