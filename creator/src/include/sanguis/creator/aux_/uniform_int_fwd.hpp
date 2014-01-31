#ifndef SANGUIS_CREATOR_AUX__UNIFORM_INT_FWD_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX__UNIFORM_INT_FWD_HPP_INCLUDED

#include <sanguis/creator/aux_/uniform_int_wrapper_fwd.hpp>
#include <fcppt/random/distribution/parameters/uniform_int_fwd.hpp>


namespace sanguis
{
namespace creator
{
namespace aux_
{

template<
	typename Type
>
using
uniform_int
=
fcppt::random::distribution::parameters::uniform_int<
	Type,
	sanguis::creator::aux_::uniform_int_wrapper
>;

}
}
}

#endif
