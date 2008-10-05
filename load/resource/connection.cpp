#include "connection.hpp"
#include "environment.hpp"
#include "../../exception.hpp"
#include <sge/texture/fragmented.hpp> // FIXME: just a quick hack, I shouldn't have to include this

sanguis::load::resource::connection::connection(
	sge::image::loader_ptr const pm,
	sge::renderer::device_ptr const rend,
	sge::audio::multi_loader &ml,
	sge::audio::player_ptr const player) 
{
	if (global_env())
		throw exception(SGE_TEXT("tried to register a resource connection a second time (check for two instances of the reousrce::connection class)"));

	global_env() = new environment(pm,rend,ml,player);
}

sanguis::load::resource::connection::~connection() 
{ 
	delete global_env();
	global_env() = 0;
}
