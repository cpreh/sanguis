#ifndef SANGUIS_TILES_IMPL_OPTIONAL_CONTENT_PATH_FWD_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_OPTIONAL_CONTENT_PATH_FWD_HPP_INCLUDED

#include <sanguis/tiles/impl/content_path_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sanguis::tiles::impl
{

using
optional_content_path
=
fcppt::optional::object<
	sanguis::tiles::impl::content_path
>;

}

#endif
