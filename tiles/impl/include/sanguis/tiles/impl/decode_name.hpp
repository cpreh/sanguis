#ifndef SANGUIS_TILES_IMPL_DECODE_NAME_HPP_INCLUDED
#define SANGUIS_TILES_IMPL_DECODE_NAME_HPP_INCLUDED

#include <sanguis/tiles/impl/optional_orientation.hpp>
#include <fcppt/string.hpp>


namespace sanguis::tiles::impl
{

sanguis::tiles::impl::optional_orientation
decode_name(
	fcppt::string const &
);

}

#endif
