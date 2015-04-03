#ifndef SANGUIS_CREATOR_IMPL_RANDOM_UNIFORM_INT_WRAPPER_DECL_HPP_INCLUDED
#define SANGUIS_CREATOR_IMPL_RANDOM_UNIFORM_INT_WRAPPER_DECL_HPP_INCLUDED

#include <sanguis/creator/impl/random/uniform_int_distribution_decl.hpp>
#include <sanguis/creator/impl/random/uniform_int_wrapper_fwd.hpp>


namespace sanguis
{
namespace creator
{
namespace impl
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
		sanguis::creator::impl::random::uniform_int_distribution<
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
