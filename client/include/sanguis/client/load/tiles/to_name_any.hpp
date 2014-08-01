#ifndef SANGUIS_CLIENT_LOAD_TILES_TO_NAME_ANY_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_TILES_TO_NAME_ANY_HPP_INCLUDED

#include <sanguis/creator/background_tile_fwd.hpp>
#include <sanguis/creator/tile_fwd.hpp>
#include <fcppt/string.hpp>


namespace sanguis
{
namespace client
{
namespace load
{
namespace tiles
{

fcppt::string
to_name_any(
	sanguis::creator::tile
);

fcppt::string
to_name_any(
	sanguis::creator::background_tile
);

}
}
}
}

#endif
