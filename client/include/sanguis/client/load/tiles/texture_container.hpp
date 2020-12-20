#ifndef SANGUIS_CLIENT_LOAD_TILES_TEXTURE_CONTAINER_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_TILES_TEXTURE_CONTAINER_HPP_INCLUDED

#include <sge/texture/const_part_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace load
{
namespace tiles
{

using
texture_container
=
std::vector<
	sge::texture::const_part_unique_ptr
>;

}
}
}
}

#endif
