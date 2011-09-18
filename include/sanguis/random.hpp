#ifndef SANGUIS_RANDOM_HPP_INCLUDED
#define SANGUIS_RANDOM_HPP_INCLUDED

#include <fcppt/tr1/random.hpp>

namespace sanguis
{

// FIXME!
typedef std::tr1::minstd_rand rand_gen_type;

rand_gen_type create_seeded_randgen();

}

#endif
