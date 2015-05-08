#ifndef SANGUIS_TILES_IMPL_MAKE_ELEMENT_MAP_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_MAKE_ELEMENT_MAP_HPP_INCLUDED

#include <sanguis/tiles/element_map.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace tiles
{
namespace impl
{

sanguis::tiles::element_map
make_element_map(
	sge::image2d::view::const_object const &,
	boost::filesystem::path const &
);

}
}
}

#endif
