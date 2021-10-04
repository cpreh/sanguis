#ifndef SANGUIS_CREATOR_TILE_SIZE_HPP_INCLUDED
#define SANGUIS_CREATOR_TILE_SIZE_HPP_INCLUDED

#include <sanguis/creator/size_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sanguis::creator
{

using
tile_size
=
std::integral_constant<
	sanguis::creator::size_type,
	96 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
>;

}

#endif
