#ifndef SANGUIS_SERVER_RANDOM_MIN_HPP_INCLUDED
#define SANGUIS_SERVER_RANDOM_MIN_HPP_INCLUDED

#include <sanguis/server/random/amount.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sanguis
{
namespace server
{
namespace random
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sanguis::server::random::amount,
	min
);

}
}
}

#endif
