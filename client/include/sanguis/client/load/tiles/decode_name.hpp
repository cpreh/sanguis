#ifndef SANGUIS_CLIENT_LOAD_TILES_DECODE_NAME_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_TILES_DECODE_NAME_HPP_INCLUDED

#include <sanguis/client/load/tiles/optional_orientation.hpp>
#include <fcppt/string.hpp>


namespace sanguis
{
namespace client
{
namespace load
{
namespace tiles
{

sanguis::client::load::tiles::optional_orientation const
decode_name(
	fcppt::string const &
);

}
}
}
}

#endif
