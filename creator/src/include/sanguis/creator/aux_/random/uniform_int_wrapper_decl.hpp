#ifndef SANGUIS_CREATOR_AUX__RANDOM_UNIFORM_INT_WRAPPER_DECL_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX__RANDOM_UNIFORM_INT_WRAPPER_DECL_HPP_INCLUDED

#include <sanguis/creator/aux_/random/uniform_int_distribution_decl.hpp>
#include <sanguis/creator/aux_/random/uniform_int_wrapper_fwd.hpp>


namespace sanguis
{
namespace creator
{
namespace aux_
{
namespace random
{

struct uniform_int_wrapper
{
	template<
		typename Type
	>
	struct apply
	{
		typedef
		sanguis::creator::aux_::random::uniform_int_distribution<
			Type
		>
		type;
	};
};

}
}
}
}

#endif
