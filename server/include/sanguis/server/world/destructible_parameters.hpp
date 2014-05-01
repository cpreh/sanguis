#ifndef SANGUIS_SERVER_WORLD_DESTRUCTIBLE_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_DESTRUCTIBLE_PARAMETERS_HPP_INCLUDED

#include <sanguis/creator/destructible_fwd.hpp>
#include <sanguis/server/entities/insert_parameters_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace world
{

sanguis::server::entities::insert_parameters const
destructible_parameters(
	sanguis::creator::destructible const &
);

}
}
}

#endif
