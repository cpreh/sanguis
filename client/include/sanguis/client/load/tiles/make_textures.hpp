#ifndef SANGUIS_CLIENT_LOAD_TILES_MAKE_TEXTURES_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_TILES_MAKE_TEXTURES_HPP_INCLUDED

#include <sanguis/client/load/tiles/texture_container.hpp>
#include <sanguis/tiles/area_container.hpp>
#include <sge/texture/part_fwd.hpp>

namespace sanguis::client::load::tiles
{

sanguis::client::load::tiles::texture_container
make_textures(sge::texture::part const &, sanguis::tiles::area_container const &);

}

#endif
