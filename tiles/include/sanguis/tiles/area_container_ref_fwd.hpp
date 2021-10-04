#ifndef SANGUIS_TILES_AREA_CONTAINER_REF_FWD_HPP_INCLUDED
#define SANGUIS_TILES_AREA_CONTAINER_REF_FWD_HPP_INCLUDED

#include <sanguis/tiles/area_container.hpp>
#include <fcppt/reference_fwd.hpp>


namespace sanguis::tiles
{

using
area_container_ref
=
fcppt::reference<
	sanguis::tiles::area_container const
>;

}

#endif
