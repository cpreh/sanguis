#ifndef SANGUIS_TILES_AREA_CONTAINER_REF_FWD_HPP_INCLUDED
#define SANGUIS_TILES_AREA_CONTAINER_REF_FWD_HPP_INCLUDED

#include <sanguis/tiles/area_container.hpp>
#include <fcppt/reference_wrapper_fwd.hpp>


namespace sanguis
{
namespace tiles
{

typedef
fcppt::reference_wrapper<
	sanguis::tiles::area_container const
>
area_container_ref;

}
}

#endif
