#ifndef SANGUIS_CLIENT_LOAD_TILES_CONST_OPTIONAL_TEXTURE_CONTAINER_REF_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_TILES_CONST_OPTIONAL_TEXTURE_CONTAINER_REF_FWD_HPP_INCLUDED

#include <sanguis/client/load/tiles/texture_container.hpp>
#include <fcppt/optional_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace load
{
namespace tiles
{

typedef
fcppt::optional<
	sanguis::client::load::tiles::texture_container const &
>
const_optional_texture_container_ref;

}
}
}
}

#endif
