#ifndef SANGUIS_CREATOR_AUX__RANDOM_UNIFORM_SIZE_FWD_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX__RANDOM_UNIFORM_SIZE_FWD_HPP_INCLUDED

#include <sanguis/creator/size_type.hpp>
#include <sanguis/creator/aux_/random/uniform_int_fwd.hpp>
#include <fcppt/random/distribution/basic_fwd.hpp>


namespace sanguis
{
namespace creator
{
namespace aux_
{
namespace random
{

typedef
fcppt::random::distribution::basic<
	sanguis::creator::aux_::random::uniform_int<
		sanguis::creator::size_type
	>
>
uniform_size;

}
}
}
}

#endif
