#ifndef SANGUIS_SERVER_WORLD_SPAWN_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_SPAWN_PARAMETERS_HPP_INCLUDED

#include <sanguis/creator/spawn_fwd.hpp>
#include <sanguis/server/entities/insert_parameters_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace world
{

sanguis::server::entities::insert_parameters
spawn_parameters(
	sanguis::creator::spawn const &
);

}
}
}

#endif
