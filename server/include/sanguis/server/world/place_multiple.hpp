#ifndef SANGUIS_SERVER_WORLD_PLACE_MULTIPLE_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_PLACE_MULTIPLE_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/creator/pos_fwd.hpp>
#include <sanguis/server/model_size_fwd.hpp>
#include <sanguis/server/world/insert_pair_container.hpp>
#include <sanguis/server/world/place_callback.hpp>


namespace sanguis
{
namespace server
{
namespace world
{

sanguis::server::world::insert_pair_container
place_multiple(
	sanguis::random_generator &,
	sanguis::server::world::place_callback const &,
	sanguis::creator::pos,
	sanguis::server::model_size
);

}
}
}

#endif
