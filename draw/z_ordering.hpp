#ifndef SANGUIS_DRAW_Z_ORDERING_HPP_INCLUDED
#define SANGUIS_DRAW_Z_ORDERING_HPP_INCLUDED

namespace sanguis
{
namespace draw
{
namespace z_ordering
{

enum type {
	background,
	corpses,
	model_generic,
	player_lower,
	bullet,
	pickup,
	player_upper,
	healthbar_lower,
	healthbar_upper,
	smoke,
	flare,
	rubble,
	cursor
};

}
}
}

#endif
