#ifndef SANGUIS_TILES_ORIENTATION_FWD_HPP_INCLUDED
#define SANGUIS_TILES_ORIENTATION_FWD_HPP_INCLUDED

#include <sanguis/tiles/direction.hpp>
#include <fcppt/container/bitfield/object_from_enum.hpp>


namespace sanguis
{
namespace tiles
{

typedef
fcppt::container::bitfield::object_from_enum<
	sanguis::tiles::direction
>
orientation;

}
}

#endif
