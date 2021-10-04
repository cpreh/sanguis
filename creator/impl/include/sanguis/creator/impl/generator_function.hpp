#ifndef SANGUIS_CREATOR_IMPL_GENERATOR_FUNCTION_HPP_INCLUDED
#define SANGUIS_CREATOR_IMPL_GENERATOR_FUNCTION_HPP_INCLUDED

#include <sanguis/creator/impl/parameters_fwd.hpp>
#include <sanguis/creator/impl/result_fwd.hpp>


namespace sanguis::creator::impl
{

using
generator_function
=
sanguis::creator::impl::result
(*)(
	sanguis::creator::impl::parameters const &
);

}

#endif
