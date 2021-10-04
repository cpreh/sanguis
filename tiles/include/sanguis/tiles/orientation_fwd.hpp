#ifndef SANGUIS_TILES_ORIENTATION_FWD_HPP_INCLUDED
#define SANGUIS_TILES_ORIENTATION_FWD_HPP_INCLUDED

#include <sanguis/tiles/direction.hpp>
#include <fcppt/container/bitfield/object_fwd.hpp>


namespace sanguis::tiles
{

using
orientation
=
fcppt::container::bitfield::object<
	sanguis::tiles::direction
>;

}

#endif
