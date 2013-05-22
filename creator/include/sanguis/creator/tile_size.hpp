#ifndef SANGUIS_CREATOR_TILE_SIZE_HPP_INCLUDED
#define SANGUIS_CREATOR_TILE_SIZE_HPP_INCLUDED

#include <sanguis/creator/size_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace creator
{

typedef std::integral_constant<
	sanguis::creator::size_type,
	64
> tile_size;

}
}

#endif
