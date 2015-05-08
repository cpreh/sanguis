#ifndef SANGUIS_TILES_ELEMENT_MAP_HPP_INCLUDED
#define SANGUIS_TILES_ELEMENT_MAP_HPP_INCLUDED

#include <sanguis/tiles/orientation.hpp>
#include <sanguis/tiles/view_container.hpp>
#include <fcppt/container/bitfield/std_hash.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace tiles
{

typedef
std::unordered_map<
	sanguis::tiles::orientation,
	sanguis::tiles::view_container
>
element_map;

}
}

#endif
