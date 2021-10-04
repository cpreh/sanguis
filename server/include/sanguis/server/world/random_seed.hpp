#ifndef SANGUIS_SERVER_WORLD_RANDOM_SEED_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_RANDOM_SEED_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/creator/seed.hpp>


namespace sanguis::server::world
{

sanguis::creator::seed
random_seed(
	sanguis::random_generator & // NOLINT(google-runtime-references)
); // NOLINT(google-runtime-references)

}

#endif
