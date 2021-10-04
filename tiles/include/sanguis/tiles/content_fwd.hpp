#ifndef SANGUIS_TILES_CONTENT_FWD_HPP_INCLUDED
#define SANGUIS_TILES_CONTENT_FWD_HPP_INCLUDED

#include <sanguis/tiles/error_fwd.hpp>
#include <sanguis/tiles/area_container_ref_fwd.hpp>
#include <fcppt/variant/object_fwd.hpp>


namespace sanguis::tiles
{

using
content
=
fcppt::variant::object<
	sanguis::tiles::area_container_ref,
	sanguis::tiles::error
>;

}

#endif
