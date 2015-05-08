#ifndef SANGUIS_TILES_IMPL_MAKE_VIEWS_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_MAKE_VIEWS_HPP_INCLUDED

#include <sanguis/tiles/view_container.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/parse/json/value_fwd.hpp>


namespace sanguis
{
namespace tiles
{
namespace impl
{

sanguis::tiles::view_container
make_views(
	sge::image2d::view::const_object const &,
	sge::parse::json::value const &
);

}
}
}

#endif
