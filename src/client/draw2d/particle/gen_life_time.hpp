#ifndef SANGUIS_CLIENT_DRAW2D_PARTICLE_GEN_LIFE_TIME_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_PARTICLE_GEN_LIFE_TIME_HPP_INCLUDED

#include "../../../time_delta.hpp"
#include <fcppt/strong_typedef.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace particle
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sanguis::time_delta,
	gen_life_time
);

}
}
}
}

#endif
