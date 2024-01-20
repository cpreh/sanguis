#ifndef SANGUIS_SERVER_RANDOM_MIN_HPP_INCLUDED
#define SANGUIS_SERVER_RANDOM_MIN_HPP_INCLUDED

#include <sanguis/server/random/amount.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef_impl.hpp> // IWYU pragma: keep

namespace sanguis::server::random
{

FCPPT_DECLARE_STRONG_TYPEDEF(sanguis::server::random::amount, min);

}

#endif
