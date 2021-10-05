#ifndef SANGUIS_SERVER_RANDOM_MAX_HPP_INCLUDED
#define SANGUIS_SERVER_RANDOM_MAX_HPP_INCLUDED

#include <sanguis/server/random/amount.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sanguis::server::random
{

FCPPT_DECLARE_STRONG_TYPEDEF(
	sanguis::server::random::amount,
	max
);

}

#endif
