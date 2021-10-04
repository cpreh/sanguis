#ifndef SANGUIS_SERVER_WORLD_PLACE_MULTIPLE_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_PLACE_MULTIPLE_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/creator/pos_fwd.hpp>
#include <sanguis/server/radius_fwd.hpp>
#include <sanguis/server/world/insert_with_id_pair_container.hpp>
#include <sanguis/server/world/place_with_id_callback.hpp>


namespace sanguis::server::world
{

sanguis::server::world::insert_with_id_pair_container
place_multiple(
	sanguis::random_generator &, // NOLINT(google-runtime-references)
	sanguis::server::world::place_with_id_callback const &,
	sanguis::creator::pos const &,
	sanguis::server::radius
);

}

#endif
