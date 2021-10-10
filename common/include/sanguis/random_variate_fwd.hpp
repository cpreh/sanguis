#ifndef SANGUIS_RANDOM_VARIATE_FWD_HPP_INCLUDED
#define SANGUIS_RANDOM_VARIATE_FWD_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <fcppt/random/variate_fwd.hpp>

namespace sanguis
{

template <typename Distribution>
using random_variate = fcppt::random::variate<sanguis::random_generator, Distribution>;

}

#endif
