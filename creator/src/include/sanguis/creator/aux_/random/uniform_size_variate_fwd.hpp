#ifndef SANGUIS_CREATOR_AUX__RANDOM_UNIFORM_SIZE_VARIATE_FWD_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX__RANDOM_UNIFORM_SIZE_VARIATE_FWD_HPP_INCLUDED

#include <sanguis/creator/aux_/random/generator_fwd.hpp>
#include <sanguis/creator/aux_/random/uniform_size_fwd.hpp>
#include <fcppt/random/variate_fwd.hpp>


namespace sanguis
{
namespace creator
{
namespace aux_
{
namespace random
{

typedef
fcppt::random::variate<
	sanguis::creator::aux_::random::generator,
	sanguis::creator::aux_::random::uniform_size
>
uniform_size_variate;

}
}
}
}

#endif
