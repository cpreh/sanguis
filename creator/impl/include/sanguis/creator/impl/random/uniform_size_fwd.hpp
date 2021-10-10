#ifndef SANGUIS_CREATOR_IMPL_RANDOM_UNIFORM_SIZE_FWD_HPP_INCLUDED
#define SANGUIS_CREATOR_IMPL_RANDOM_UNIFORM_SIZE_FWD_HPP_INCLUDED

#include <sanguis/creator/size_type.hpp>
#include <sanguis/creator/impl/random/uniform_int_fwd.hpp>
#include <fcppt/random/distribution/basic_fwd.hpp>

namespace sanguis::creator::impl::random
{

using uniform_size = fcppt::random::distribution::basic<
    sanguis::creator::impl::random::uniform_int<sanguis::creator::size_type>>;

}

#endif
