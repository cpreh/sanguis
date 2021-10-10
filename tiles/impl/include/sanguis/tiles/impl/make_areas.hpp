#ifndef SANGUIS_TILES_IMPL_MAKE_AREAS_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_MAKE_AREAS_HPP_INCLUDED

#include <sanguis/tiles/area_container.hpp>
#include <sge/image2d/dim_fwd.hpp>
#include <sge/parse/json/value_fwd.hpp>

namespace sanguis::tiles::impl
{

sanguis::tiles::area_container
make_areas(sge::image2d::dim const &, sge::parse::json::value const &);

}

#endif
