#ifndef SANGUIS_TILES_AREA_CONTAINER_HPP_INCLUDED
#define SANGUIS_TILES_AREA_CONTAINER_HPP_INCLUDED

#include <sge/image2d/rect.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace tiles
{

typedef
std::vector<
	sge::image2d::rect
>
area_container;

}
}

#endif