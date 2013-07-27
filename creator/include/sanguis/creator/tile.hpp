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
	door,
	concrete_wall,
	fcppt_maximum = concrete_wall
};

}
}

#endif
