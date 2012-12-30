#ifndef SANGUIS_CLIENT_DRAW2D_Z_ORDERING_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_Z_ORDERING_HPP_INCLUDED

#include <sanguis/client/draw2d/z_ordering_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{

enum class z_ordering
{
	background,
	corpses,
	model_generic,
	player_lower,
	bullet,
	pickup,
	player_upper,
	healthbar_lower,
	healthbar_upper,
	size
};

}
}
}

#endif
