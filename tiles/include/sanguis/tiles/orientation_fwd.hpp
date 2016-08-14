#ifndef SANGUIS_TILES_ORIENTATION_FWD_HPP_INCLUDED
#define SANGUIS_TILES_ORIENTATION_FWD_HPP_INCLUDED

#include <sanguis/tiles/direction.hpp>
#include <fcppt/container/bitfield/enum_object_fwd.hpp>


namespace sanguis
{
namespace tiles
{

typedef
fcppt::container::bitfield::enum_object<
	sanguis::tiles::direction
>
orientation;

}
}

#endif
