#ifndef SANGUIS_CLIENT_DRAW2D_Z_ORDERING_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_Z_ORDERING_HPP_INCLUDED

namespace sanguis
{
namespace client
{
namespace draw2d
{

namespace z_ordering
{
enum type
{
	background,
	corpses,
	model_generic,
	player_lower,
	bullet,
	pickup,
	player_upper,
	smoke,
	flare,
	rubble,
	healthbar_lower,
	healthbar_upper,
	size
};
}

}
}
}

#endif
