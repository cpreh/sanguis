#ifndef SANGUIS_LOAD_TILES_ORIENTATION_FWD_HPP_INCLUDED
#define SANGUIS_LOAD_TILES_ORIENTATION_FWD_HPP_INCLUDED

#include <fcppt/container/bitfield/object_from_enum.hpp>
#include <sanguis/load/tiles/direction.hpp>


namespace sanguis
{
namespace load
{
namespace tiles
{

typedef
fcppt::container::bitfield::object_from_enum<
	sanguis::load::tiles::direction
>
orientation;

}
}
}

#endif
