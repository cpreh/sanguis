#ifndef SANGUIS_CREATOR_IMPL_RANDOM_UNIFORM_SIZE_VARIATE_FWD_HPP_INCLUDED
#define SANGUIS_CREATOR_IMPL_RANDOM_UNIFORM_SIZE_VARIATE_FWD_HPP_INCLUDED

#include <sanguis/creator/impl/random/generator_fwd.hpp>
#include <sanguis/creator/impl/random/uniform_size_fwd.hpp>
#include <fcppt/random/variate_fwd.hpp>

namespace sanguis::creator::impl::random
{

using uniform_size_variate = fcppt::random::variate<
    sanguis::creator::impl::random::generator,
    sanguis::creator::impl::random::uniform_size>;

}

#endif
