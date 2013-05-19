#ifndef SANGUIS_CREATOR_TILE_HPP_INCLUDED
#define SANGUIS_CREATOR_TILE_HPP_INCLUDED

#include <sanguis/creator/tile_fwd.hpp>


namespace sanguis
{
namespace creator
{

enum class tile
{
	nothing,
	concrete_wall,
	concrete_wall_broken,
	fcppt_maximum = concrete_wall_broken
};

}
}

#endif
