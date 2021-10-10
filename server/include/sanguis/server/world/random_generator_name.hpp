#ifndef SANGUIS_SERVER_WORLD_RANDOM_GENERATOR_NAME_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_RANDOM_GENERATOR_NAME_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/creator/name.hpp>

namespace sanguis::server::world
{

sanguis::creator::name
random_generator_name(sanguis::random_generator & // NOLINT(google-runtime-references)
); // NOLINT(google-runtime-references)

}

#endif
