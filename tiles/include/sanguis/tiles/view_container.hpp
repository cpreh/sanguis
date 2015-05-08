#ifndef SANGUIS_TILES_VIEW_CONTAINER_HPP_INCLUDED
#define SANGUIS_TILES_VIEW_CONTAINER_HPP_INCLUDED

#include <sge/image2d/view/const_object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace tiles
{

typedef
std::vector<
	sge::image2d::view::const_object
>
view_container;

}
}

#endif
