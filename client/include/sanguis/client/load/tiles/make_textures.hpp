#ifndef SANGUIS_CLIENT_LOAD_TILES_MAKE_TEXTURES_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_TILES_MAKE_TEXTURES_HPP_INCLUDED

#include <sanguis/client/load/tiles/texture_container.hpp>
#include <sge/parse/json/value_fwd.hpp>
#include <sge/texture/part_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace load
{
namespace tiles
{

sanguis::client::load::tiles::texture_container
make_textures(
	sge::texture::part const &,
	sge::parse::json::value const &
);

}
}
}
}

#endif