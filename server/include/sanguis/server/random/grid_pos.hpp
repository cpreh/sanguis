#ifndef SANGUIS_SERVER_RANDOM_GRID_POS_HPP_INCLUDED
#define SANGUIS_SERVER_RANDOM_GRID_POS_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/creator/dim_fwd.hpp>
#include <sanguis/creator/pos.hpp>


namespace sanguis
{
namespace server
{
namespace random
{

sanguis::creator::pos const
grid_pos(
	sanguis::random_generator &,
	sanguis::creator::dim
);

}
}
}

#endif
