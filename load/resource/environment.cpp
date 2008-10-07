#include "environment.hpp"
#include <sge/texture/default_creator_impl.hpp>
#include <sge/texture/no_fragmented.hpp>
#include <sge/audio/player.hpp>
#include <ctime>
#include <cstdlib>

sanguis::load::resource::environment *&sanguis::load::resource::global_env()
{
	static environment *ptr = 0;
	return ptr;
}

sanguis::load::resource::environment::environment(
	sge::image::loader_ptr const il,
	sge::renderer::device_ptr const r,
	sge::audio::multi_loader &ml,
	sge::audio::player_ptr const player) 
: rend(r),
  il(il),
	ml(ml),
	player(player),
  texman(
  	rend,
	sge::texture::default_creator<sge::texture::no_fragmented>(
		rend,
		sge::renderer::linear_filter))
{
	load_textures();
}
