#ifndef SANGUIS_SERVER_WORLD_RANDOM_SEED_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_RANDOM_SEED_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/creator/seed.hpp>


namespace sanguis
{
namespace server
{
namespace world
{

sanguis::creator::seed const
random_seed(
	sanguis::random_generator &
);

}
}
}

#endif
