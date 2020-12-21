#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_MAKE_TEXTURE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_MAKE_TEXTURE_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/client/draw/debug.hpp>
#include <sanguis/client/load/tiles/context_ref.hpp>
#include <sanguis/tiles/content_fwd.hpp>
#include <sge/texture/const_optional_part_ref.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace scene
{
namespace world
{

sge::texture::const_optional_part_ref
make_texture(
	sanguis::random_generator &, // NOLINT(google-runtime-references)
	sanguis::client::draw::debug,
	sanguis::client::load::tiles::context_ref,
	std::filesystem::path const &,
	sanguis::tiles::content const &
);

}
}
}
}
}

#endif
