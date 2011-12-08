#ifndef SANGUIS_RANDOM_HPP_INCLUDED
#define SANGUIS_RANDOM_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <boost/random/linear_congruential.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{

// FIXME!
typedef boost::random::minstd_rand rand_gen_type;

rand_gen_type create_seeded_randgen();

}

#endif
