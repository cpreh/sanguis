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
	ground,
	destructible,
	pickup,
	aura,
	model_generic,
	player_lower,
	bullet_tail,
	bullet,
	player_upper,
	flare,
	text,
	fcppt_maximum = text
};

}
}
}

#endif
