#ifndef SANGUIS_TILES_CONTENT_FWD_HPP_INCLUDED
#define SANGUIS_TILES_CONTENT_FWD_HPP_INCLUDED

#include <sanguis/tiles/error_fwd.hpp>
#include <sanguis/tiles/area_container_ref_fwd.hpp>
#include <fcppt/variant/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace tiles
{

typedef
fcppt::variant::object<
	boost::mpl::vector2<
		sanguis::tiles::area_container_ref,
		sanguis::tiles::error
	>
>
content;

}
}

#endif
