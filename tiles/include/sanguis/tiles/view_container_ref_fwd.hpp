#ifndef SANGUIS_TILES_VIEW_CONTAINER_REF_FWD_HPP_INCLUDED
#define SANGUIS_TILES_VIEW_CONTAINER_REF_FWD_HPP_INCLUDED

#include <sanguis/tiles/view_container.hpp>
#include <fcppt/reference_wrapper_fwd.hpp>


namespace sanguis
{
namespace tiles
{

typedef
fcppt::reference_wrapper<
	sanguis::tiles::view_container const
>
view_container_ref;

}
}

#endif
